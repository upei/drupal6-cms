<?php
// $Id: feedapi_mapper_date.inc,v 1.1.2.3.2.2 2009/02/10 20:32:43 alexb Exp $

/**
 * Implementation of hook_feedapi_mapper for date field from content.module (CCK),
 *
 * @param string $op
 * @param Drupal node $node
 * @param string $field_name
 * @param string, number or array of string or number $feed_element
 * @param string or number as id $sub_field
 * 
 */
function date_feedapi_mapper($op, &$node, $field_name, $feed_element = array(), $sub_field = '') {
  if (!$field = feedapi_mapper_content_is_cck_type($field_name, array('date', 'datestamp', 'datetime'))) {
    // if not a date just return
    return;
  }
  
  switch ($op) {
    case 'describe':
      // Describe what we are doing in this mapper. This shows up as help text on the mapping page. 
      return t('Maps a date to a date CCK field.');
    
    case 'list':
      // Here we are being asked to list sub fields we would like to map to.
      $sub_fields = array();
      $sub_fields['ical'] = 'iCal VEVENT';
      $sub_fields['start_date'] = 'Start Date (date only)';
      $sub_fields['start_time'] = 'Start Time (time only)';
      $sub_fields['start_datetime'] = 'Start Date (date and time)';
      $sub_fields['end_date'] = 'End Date (date only)';
      $sub_fields['end_time'] = 'End Time (time only)';
      $sub_fields['end_datetime'] = 'End Date (date and time)';
      $sub_fields['all_day'] = 'All Day';
      $sub_fields['timezone'] = 'Timezone';
      return $sub_fields;
    
    case 'map':
      include_once(drupal_get_path('module', 'date_api') .'/date_api_ical.inc');
      switch ($sub_field) {
        case 'ical':
          return feedapi_mapper_date_ical($node, $field, $feed_element);
          
        case 'start_datetime':
        case 'end_datetime':
          return feedapi_mapper_date_datetime($node, $field, $feed_element, $sub_field);
            
        default:
          return feedapi_mapper_date_part($node, $field, $feed_element, $sub_field);
      }
  }
}

/**
 * Create a date from a simple string date value.
 */
function feedapi_mapper_date_datetime(&$node, $field, $feed_element, $sub_field) {
  $field_name = $field['field_name'];
  
  // Pull offset information out of datetime and reset date to
  // the known value, UTC. The offset is not useful here.
  preg_match('/(([\+\-])(\d{2})?:?(\d{2})?)/', $feed_element, $matches);
  if (!empty($matches)) {
    $datetime = trim(str_replace($matches[1], '', $feed_element));
    $timezone = 'UTC';
    $date = date_create($datetime, timezone_open('UTC'));
    $direction = $matches[2];
    $hours = $matches[3];
    $minutes = $matches[4];
    if ($hours == '00' && $minutes == '00') {
        // This is UTC, no adjustment needed.
    }
    else {
      // Bring the date back to UTC.
      date_modify($date, $direction . trim($hours) .' hours');
      date_modify($date, $direction . trim($minutes) .' minutes');       
    }
  }
  else {
    // A date without a timezone or a non-ISO date, assume local timezone.
    $timezone = date_default_timezone_name();
    $date = date_create($feed_element, timezone_open($timezone));
  }

  $date = new date_constructor();
  $date->construct($field);
  $date->set_value('timezone', $timezone);
  $date->set_value('start_datetime', $feed_element);
  //$date->set_value('end_datetime', $feed_element);
  $date->build();
  $node->$field_name = array($date->value);
  return $node;
}

/**
 * Create a date from an iCal feed array.
 */
function feedapi_mapper_date_ical($node, $field, $feed_element) {
  $field_name = $field['field_name'];
  
  $timezone = $feed_element['DTSTART']['tz'];
  if (empty($timezone)) $timezone = date_default_timezone_name();
  
  $date = new date_constructor();
  $date->construct($field);
  $date->set_value('timezone', $timezone);
  $date->set_value('start_datetime', $feed_element['DTSTART']['datetime']);
  $date->set_value('end_datetime', $feed_element['DTEND']['datetime']);
  $date->set_value('all_day', $feed_element['all_day']);
  $date->build();
  $node->$field_name = array($date->value);
        
  if (array_key_exists('RRULE', $feed_element) && !empty($feed_element['RRULE']) && module_exists('date_repeat')) {
          
    include_once('./'. drupal_get_path('module', 'date_repeat') .'/date_repeat_calc.inc');
    include_once('./'. drupal_get_path('module', 'date') .'/date_repeat.inc');

    // Explode the RRULE into parts so we can analyze it.
    $rrule = $feed_element['RRULE'] . (!empty($feed_element['EXDATE']) ? "/n". $feed_element['EXDATE'] : "");
    $form_values = date_ical_parse_rrule($field, $rrule);
          
    // Set an maximum value for repeating dates.
    // One year, 5 repeats for now, could be adjusted or made configurable later.
    $max = date_now();
    $max_repeats = 5;
      
    date_modify($max, '+1 year');
    $until = date_format($max, 'Y-m-d H:i:s');
    if (empty($form_values['UNTIL']) || $until < $form_values['UNTIL']['datetime']) {
      $form_values['UNTIL'] = array('datetime' => $until, 'tz' => 'UTC');
    }
    $form_values['COUNT'] = $max_repeats;
          
    // Reconstruct the RRULE with our changes and build the repeats.
    $rrule = date_api_ical_build_rrule($form_values);
    $node_field = $node->$field_name[0];
    $values = date_repeat_build_dates($rrule, $form_values, $field, $node_field);
    $node->$field_name = $values;

  }
  return $node;
}

/**
 * Create a date from a collection of date parts.
 * The most complicated scenario since we don't know what parts
 * we are getting or in what order. We'll create date information
 * and retain it from one element to the next to gradually build
 * up the date values. We use the current date as a default value
 * when nothing else is known.
 */
function feedapi_mapper_date_part(&$node, $field, $feed_element, $sub_field) {
  static $date;
  
  $field_name = $field['field_name'];
  if (empty($node->$field_name)) {
    $date = new date_constructor();
    $date->construct($field);
  }
  $date->set_value($sub_field, $feed_element);
  $date->build();
  $node->$field_name = array($date->value);
  return $node;
}

/**
 * Construct a date from a collection of date parts
 * that could be provided in any order, without knowing
 * ahead of time exactly which parts will be set.
 * 
 * Functions by defaulting to current date for missing values.
 * Retains previous values and continuously resets them as
 * more information becomes known.
 * 
 * Call build() at any time to construct a date from the
 * currently available values.
 *
 */
class date_constructor {
  var $field = NULL;
  var $timezone = NULL;
  var $start_date = NULL;
  var $end_date = NULL;
  var $start_time = NULL;
  var $end_time = NULL;
  var $start_datetime = NULL;
  var $end_datetime = NULL;
  var $value = NULL;
  var $format = NULL;
  var $db_tz = NULL;
  var $to_tz = NULL;
  
  function construct($field) {
    $now = date_now();  
    $this->start_date = date_format($now, DATE_FORMAT_DATE);
    $this->start_time = '00:00:00';
    $this->start_datetime = $this->start_date .' '. $this->start_time;
    $this->timezone = date_default_timezone_name();
    $this->field = $field;
    $this->format = date_type_format($field['type']);
  }

  function set_value($key, $value) {
    switch ($key) {
      case 'timezone':
        $this->timezone = $value;
        break;
      case 'all_day':
        if (!empty($value) && strtolower($value) != 'false' && $value !== FALSE) {
          $this->start_time = '00:00:00';
          $this->end_time = '00:00:00';
          $this->start_datetime = $this->start_date .' '. $this->start_time;
          $this->end_datetime = $this->end_date .' '. $this->end_time;
        }
        break;
      case 'start_date':
        $this->start_date = $value;
        $this->start_datetime = $this->start_date .' '. $this->start_time;
        break;
      case 'start_time':
        $this->start_time = $value;
        $this->start_datetime = $this->start_date .' '. $this->start_time;
        break;
      case 'end_date':
        $this->end_date = $value;
        $this->end_datetime = $this->end_date .' '. $this->end_time;
        break;
      case 'end_time':
        $this->end_time = $value;
        $this->end_datetime = $this->end_date .' '. $this->end_time;
        break;
      case 'start_datetime':
        $this->start_datetime = $value;
        break;
      case 'end_datetime':
        $this->end_datetime = $value;
        break;  
  
    }
  }

  function set_timezone() {
    $this->db_tz = date_get_timezone_db($this->field['tz_handling'], $this->timezone);
    $this->to_tz = date_get_timezone($this->field['tz_handling'], $this->timezone);
  }

  /**
   * Create date objects with the known values.
   */
  function build() {
    $this->set_timezone();
    if (empty($this->start_datetime)) {
      $this->start_datetime = $this->start_date .' '. $this->start_time;
    }
    if (empty($this->end_date)) {
      $this->end_date = $this->start_date;
    }
    if (empty($this->end_time)) {
      $this->end_time = $this->start_time;
    }
    if (empty($this->end_datetime)) {
      $this->end_datetime = $this->end_date .' '. $this->end_time;
    }
    // We don't know exactly what format the provided date used,
    // so use the native date_create() where available, which does a
    // pretty good job of interpreting non-standard date values. Where the 
    // native date_create() is not available (PHP 4, PHP 5.0 and PHP 5.1)
    // use strtotime() as the best available interpreter of irregularly
    // formated date values.
    if (version_compare(PHP_VERSION, '5.2', '<')) {
      $timestamp = strtotime($this->start_datetime);
      $this->value['date'] = date_create("@$timestamp");
      $timestamp = strtotime($this->end_datetime);
      $this->value['date2'] = date_create("@$timestamp");
    }
    else {
      $this->value['date'] = date_create($this->start_datetime, timezone_open($this->to_tz));
      $this->value['date2'] = date_create($this->end_datetime, timezone_open($this->to_tz));      
    }
    $this->value['offset'] = date_offset_get($this->value['date']);
    $this->value['offset2'] = date_offset_get($this->value['date2']);
    date_timezone_set($this->value['date'], timezone_open($this->db_tz));
    date_timezone_set($this->value['date2'], timezone_open($this->db_tz));
    $this->value['value'] = date_format($this->value['date'], $this->format);
    $this->value['value2'] = date_format($this->value['date2'], $this->format);
    $this->value['timezone'] = $this->to_tz;
    dsm($this->value);
  }
}
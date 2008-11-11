<?php
// $Id: feedapi_mapper_date.inc,v 1.1.2.3.2.1 2008/09/08 11:41:13 alexb Exp $

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
function date_feedapi_mapper($op, $node, $field_name, $feed_element = array(), $sub_field = '') {
  if (!$field = feedapi_mapper_content_is_cck_type($field_name, array('date', 'datestamp'))) {
    // if not a date just return
    return;
  }

  switch ($op) {
    case 'describe':
      // Describe what we are doing in this mapper. This shows up as help text on the mapping page.
      return t('Maps a date to a date CCK field.');
    case 'list':
      // just for sub_fields
      return TRUE;
    case 'map':
      // Here is where the actual mapping happens.
      include_once(drupal_get_path('module', 'date_api') .'/date.inc');
      $items = $node->$field_name;
      if (!is_array($feed_element)) {
        // TODO TIMEZONE
        // Don't know what type of date so first attempt to create a date from a string
        $date = date_text_make_dbdate($feed_element, $field['type'], '', 'none', date_granularity_array($field));
        if ($date->db->timestamp == '') {
          // not from string, use the empty date object and try as a datestamp
          date_set_date($date, $feed_element, 'none', 'db', DATE_UNIX);
          // Note granularity is also done on submit
        }
      }

      if ($field['type'] == DATE_ISO) {
        $items[]['value'] = $date->db->iso;
      }
      else {
        $items[]['value'] = $date->db->timestamp;
      }
      $node->$field_name = $items;
      return $node;
  }
}

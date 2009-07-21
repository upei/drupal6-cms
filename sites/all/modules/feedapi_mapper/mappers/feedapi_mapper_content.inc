<?php
// $Id: feedapi_mapper_content.inc,v 1.1.2.4.2.5 2009/06/25 17:14:22 alexb Exp $

/**
 * On behalf implementation of hook_feedapi_mapper for content.module (CCK).
 *
 * @see hook_feedapi_mapper()
 */
function content_feedapi_mapper($op, $node, $feed_element = array(), $field_name = '', $sub_field = '') {
  // Test for the node field that we would like to map to.
  if ($op == 'describe') {
    return t('Maps a string or a number to this CCK field.');
  }
  else if ($op == 'list') {
    $info = content_types($node->type);
    $fields = array();
    if (@count($info['fields'])) {
      foreach ($info['fields'] as $field_name => $field) {
        if (in_array($field['type'], array('text', 'number_integer', 'number_decimal'))) {
          $fields[$field_name] = isset($field['widget']['label']) ? $field['widget']['label'] : $field_name;
        }
      }
    }
    if (count($fields)) {
      return $fields;
    }
    return FALSE;
  }
  else if ($op == 'map') {
    // Here is where the actual mapping happens.
    // When we are called at this point, $field_name contains the name of the field the user has
    // decided to map to and $field_element is the feed item element the user has decided to map.
    // We just need to put the two things together. The data structure here depends a lot on
    // CCK. We stick the value in $feed_element into $node->$field_name[0]['value'].
    $field = isset($node->$field_name) ? $node->$field_name : array();
    if (is_array($feed_element)) {
      $i = 0;
      foreach ($feed_element as $value) {
        if (!is_array($value) && !is_object($value)) {
          $field[$i]['value'] = $value;
        }
        $i++;
      }
    }
    else {
      $field[0]['value'] = $feed_element;
    }
    $node->$field_name = $field;
    return $node;
  }
}
<?php
// $Id: feedapi_mapper_content.inc,v 1.1.2.4.2.2 2008/10/27 00:07:34 alexb Exp $

/**
 * On behalf implementation of hook_feedapi_mapper for content.module (CCK).
 *
 * @param string $op
 * @param Drupal node $node
 * @param string $field_name
 * @param string, number or array of string or number $feed_element
 * @param string or number as id $sub_field
 *
 */
function content_feedapi_mapper($op, $node, $field_name, $feed_element = array(), $sub_field = '') {
  // Test for the node field that we would like to map to.
  if (strpos($field_name, 'field_') === 0) {
    if ($op == 'describe') {
      // Describe what we are doing in this mapper. This shows up as help text on the mapping page.
      if (feedapi_mapper_content_is_cck_type($field_name, array('text', 'number_integer', 'number_decimal'))) {
        return t('Maps a string or a number to this CCK field.');
      }
    }
    else if ($op == 'list') {
      // Here we are being asked to list sub fields we would like to map to.
      if (feedapi_mapper_content_is_cck_type($field_name, array('text', 'number_integer', 'number_decimal'))) {
        return TRUE;
      }
      return FALSE;
    }
    else if ($op == 'map') {
      // Here is where the actual mapping happens.
      // When we are called at this point, $field_name contains the name of the field the user has
      // decided to map to and $field_element is the feed item element the user has decided to map.
      // We just need to put the two things together. The data structure here depends a lot on
      // CCK. We stick the value in $feed_element into $node->$field_name[0]['value'].
      if (!is_array($feed_element)) {
        $field = isset($node->$field_name) ? $node->$field_name : array();
        $field[0]['value'] = $feed_element;
        $node->$field_name = $field;
      }
      return $node;
    }
  }
}

/**
 * Determines if a given field is of a given type
 *
 * @param string $node_type
 *   Drupal content type.
 * @param string $field_name
 *   Name of the field to determine the type of.
 * @param array $field_types
 *   Array of field types that should be tested for.
 * @return unknown
 */
function feedapi_mapper_content_is_cck_type($field_name, $field_types) {
  $field = content_fields($field_name);
  if (in_array($field['type'], $field_types)) {
    return $field;
  }
  else {
    return FALSE;
  }
}
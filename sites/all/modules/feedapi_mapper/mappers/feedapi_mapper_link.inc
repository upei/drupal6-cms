<?php
// $Id: feedapi_mapper_link.inc,v 1.1.2.4.2.1 2008/09/08 11:41:13 alexb Exp $

/**
 * On behalf implementation of hook_feedapi_mapper for link.module (CCK).
 * Link module available at http://drupal.org/project/link
 * based on feedapi_mapper_content.inc
 *
 * @param string $op
 * @param Drupal node $node
 * @param string $field_name
 * @param string, number or array of string or number $feed_element
 * @param string or number as id $sub_field
 *
 */
function link_feedapi_mapper($op, $node, $field_name, $feed_element = array(), $sub_field = '') {
  // Test for the node field that we would like to map to.
  if (strpos($field_name, 'field_') === 0) {
    if ($op == 'describe') {
      if (feedapi_mapper_content_is_cck_type($field_name, array('link'))) {
        return t('Maps a URL to this link CCK field.');
      }
      // Describe what we are doing in this mapper. This shows up as help text on the mapping page.
    }
    else if ($op == 'list') {
      if (feedapi_mapper_content_is_cck_type($field_name, array('link'))) {
        return TRUE;
      }
      // Here we are being asked to list sub fields we would like to map to.
      // In this case, we only map to the CCK field or not, so we return just TRUE.
      return FALSE;
    }
    else if ($op == 'map') {
      // Here is where the actual mapping happens.
      // When we are called at this point, $field_name contains the name of the field the user has
      // decided to map to and $field_element is the feed item element the user has decided to map.
      // We just need to put the two things together. The data structure here depends a lot on
      // CCK. We stick the value in $feed_element into $node->$field_name[0]['value'].
      if (!is_array($feed_element)) {
        $field = $node->$field_name;
        $field[0]['url'] = link_validate_url($feed_element) ? $feed_element : NULL;
        $node->$field_name = $field;
        return $node;
      }
    }
  }
}

<?php
// $Id: feedapi_mapper_emvideo.inc,v 1.1.2.1 2008/10/09 15:22:53 alexb Exp $

/**
 * Implementation of hook_feedapi_mapper for emvideo part of embedded media CCK.
 *
 * @param string $op
 * @param Drupal node $node
 * @param string $field_name
 * @param string, number or array of string or number $feed_element
 * @param string or number as id $sub_field
 *
 */
function emvideo_feedapi_mapper($op, $node, $field_name, $feed_element = array(), $sub_field = '') {
  $field = content_fields($field_name);
  if ($field['type'] != 'emvideo') {
    // if not an emvideo field just return
    return;
  }

  switch ($op) {
    case 'describe':
      // Describe what we are doing in this mapper. This shows up as help text on the mapping page.
      return t('Maps a link to a video to the Embedded Media Video CCK field. Use the original_url element for mapping to this field.');
    case 'list':
      // just for sub_fields
      return TRUE;
    case 'map':
      // Here is where the actual mapping happens.
      $items = $node->$field_name;
      if (is_string($feed_element) && valid_url($feed_element)) {
        // straight link usually from options->original_url or options->guid
        $items[]['embed'] = $feed_element;
      }
      elseif (is_array($feed_element)) {
        foreach ($feed_element as $element) {
          if (is_array($element)) {
            // is this an options->enclosure-media->type array
            if (valid_url($element['link'])) {
              $items[]['embed'] = $element['link'];
            }
            elseif (valid_url($element['player'])) {
              $items[]['embed'] = $element['player'];
            }
          }
          elseif (is_string($element) && valid_url($element)) {
            // not sure when this would be called but for completeness
            $items[]['embed'] = $element;
          }
        }
      }
      emvideo_field('submit', $node, $field, $items, FALSE, FALSE);
      $node->$field_name = $items;
      return $node;
  }
}

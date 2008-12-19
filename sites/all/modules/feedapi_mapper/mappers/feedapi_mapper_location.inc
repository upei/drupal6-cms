<?php
// $Id: feedapi_mapper_location.inc,v 1.1.2.1 2008/11/14 14:44:46 alexb Exp $
/**
 * Implementation of feed element mapper for location.module.
 */

/**
 * Implementation of hook_feedapi_mapper().
 * Maps feed elements to location fields.
 * @param $op
 *   'list' or 'map'
 * @param $node
 *   Feed item node to map on.
 * @param $field_name
 *   Name of field to map to.
 * @param $feed_element
 *   Feed item element to map from. Parameter only present on $op = 'map'
 * @param @sub_field
 *   Subfield on field to map to. Parameter only present on $op = 'map'.
 *   This parameter will depend on if the hook implementation returns a subfield on 
 *   $op = 'list'.
 *
 * Return key => name array of sub fields on 'list'.
 * If only one field and no subfields are available for this content type return TRUE.
 * If no fields available for this content type return FALSE.
 * Options are necessary because a field like
 * e. g. "taxonomy" might have more than one slot for information - e. g. vocabularies.
 * 
 * Todo: $node could be passed by reference - implementers wouldn't need to return node
 * (PHP5 passes in by reference by default).
 */
function location_feedapi_mapper($op, $node, $field_name, $feed_element = array(), $sub_field = '') {
  if ($field_name == 'locations' && variable_get('location_maxnum_'. $node->type, 0)) {
    if ($op == 'describe') {
      return t('Maps pairs of geographic coordinates to the location of a node.');
    }
    else if ($op == 'list') {
      $sub_fields['latitude'] = 'Latitude';
      $sub_fields['longitude'] = 'Longitude';
      return $sub_fields;
    }
    else if ($op == 'map') {
      if (is_array($feed_element)) {
        foreach ($feed_element as $i => $val) {
          $node->locations[$i][$sub_field] = $val;
        }
      }
      return $node;
    }
  }
  else {
    return FALSE;
  }
}

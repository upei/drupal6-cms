<?php
// $Id: feedapi_mapper_taxonomy.inc,v 1.1.4.2 2008/10/27 00:07:34 alexb Exp $
/**
 * On behalf implementation of feed element mapper for taxonomy.module.
 */

/**
 * Implementation of hook_feedapi_mapper().
 * Maps feed elements to taxonomy values.
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
function taxonomy_feedapi_mapper($op, $node, $field_name, $feed_element = array(), $sub_field = '') {
  if ($field_name == 'taxonomy') {
    if ($op == 'describe') {
      return t('Maps a string or an array of strings to taxonomy terms. Chose a vocabulary from sub options.');
    }
    else if ($op == 'list') {
      if ($vocabularies = taxonomy_get_vocabularies($node->type)) {
        foreach ($vocabularies as $v) {
          $sub_fields[$v->vid] = $v->name;
        }
        return $sub_fields;
      }
      return FALSE;
    }
    else if ($op == 'map') {
      // Todo: some plausibility check of $feed_element
      // Todo: security check of $feed_element
      if (is_string($feed_element)) {
        $feed_element = array($feed_element);
      }
      if (is_array($feed_element)) {
        if (!isset($node->taxonomy) || !is_array($node->taxonomy)) {
          $node->taxonomy = array();
        }
        $node->taxonomy = array_merge($node->taxonomy, _feedapi_mapper_create_terms($feed_element, $sub_field));
      }
      return $node;
    }
  }
}

/**
 * Creates terms from keywords, borrowed from yahoo_terms module.
 * Todo: simplify.
 */
function _feedapi_mapper_create_terms($keywords, $vid, $static = FALSE) {
  if ($vid == FALSE) {
    return FALSE;
  }
  $tids = array();
  if (is_array($keywords)) {
    foreach ($keywords as $term) {
      $curr_terms = taxonomy_get_term_by_name($term);
      if (count($curr_terms) != 0) {
        foreach ($curr_terms as $curr_term) {
          if ($curr_term->vid == $vid) {
            $tids[$curr_term->tid] = $curr_term;
          }
        }
        if (count($tids) == 0 and $static == FALSE) {
          $new_term['name'] = $term;
          $new_term['vid'] = $vid;
          taxonomy_save_term($new_term);
          $tids[$new_term['tid']] = taxonomy_get_term($new_term['tid']);
          unset($new_term);
        }
      }
      else {
        if ($static == FALSE) {
          $new_term['name'] = $term;
          $new_term['vid'] = $vid;
          taxonomy_save_term($new_term);
          $tids[$new_term['tid']] = taxonomy_get_term($new_term['tid']);
          unset($new_term);
        }
      }
    }
  }
  return $tids;
}

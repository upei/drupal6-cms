<?php
// $Id: feedapi_mapper_taxonomy.inc,v 1.1.4.4 2009/04/20 13:31:04 alexb Exp $

/**
 * On behalf implementation of hook_feedapi_mapper() for taxonomy module.
 * 
 * @see hook_feedapi_mapper()
 */
function taxonomy_feedapi_mapper($op, $node, $feed_element = array(), $field_name = '', $sub_field = '') {
  if ($op == 'describe') {
    return t('Maps a string or an array of strings to taxonomy terms. Chose a vocabulary from sub options.');
  }
  else if ($op == 'list') {
    if ($vocabularies = taxonomy_get_vocabularies($node->type)) {
      foreach ($vocabularies as $v) {
        $sub_fields[$v->vid] = $v->name;
      }
      return array('taxonomy' => $sub_fields);
    }
    return FALSE;
  }
  else if ($op == 'map' && $field_name == 'taxonomy') {
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

/**
 * Creates terms from keywords, borrowed from yahoo_terms module.
 * @todo apply http://drupal.org/node/354657#comment-1184004
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

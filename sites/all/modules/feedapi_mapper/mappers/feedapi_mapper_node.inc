<?php
// $Id: feedapi_mapper_node.inc,v 1.1.2.2 2008/12/02 17:32:43 alexb Exp $
/**
 * On behalf implementation of feed element mapper for node.module.
 * 
 * @todo:
 * - modify so that per default feedapi_node module's mappings are showing 
 *   (e. g. description -> body)
 * - if default mapping is removed, nothing is mapped to target (= e. g. body 
 *   stays empty)
 */

/**
 * Implementation of hook_feedapi_mapper().
 */
function node_feedapi_mapper($op, $node, $field_name, $feed_element = array(), $sub_field = '') {
  if (in_array($field_name, array('title', 'body', 'created'))) {
    if ($op == 'describe') {
      return t('Maps a feed element to a title, created date or a body of a node. Note that standard field mapping by FeedAPI still applies. For example if there is no feed element mapped to the node body you will still find the description in node body because that is how FeedAPI stores nodes.');
    }
    else if ($op == 'list') {
      return TRUE;
    }
    else if ($op == 'map') {
      if (is_string($feed_element) || is_numeric($feed_element)) {
        $node->$field_name = $feed_element;
      }
      return $node;
    }
  }
}

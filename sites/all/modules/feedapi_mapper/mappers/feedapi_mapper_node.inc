<?php
// $Id: feedapi_mapper_node.inc,v 1.1.2.5 2009/06/19 16:52:06 aronnovak Exp $

/**
 * On behalf implementation of hook_feedapi_mapper() for node module.
 * 
 * @see hook_feedapi_mapper()
 * 
 * @todo:
 * - modify so that per default feedapi_node module's mappings are showing 
 *   (e. g. description -> body)
 * - if default mapping is removed, nothing is mapped to target (= e. g. body 
 *   stays empty)
 */
function node_feedapi_mapper($op, $node, $feed_element = array(), $field_name = '', $sub_field = '') {
  if ($op == 'describe') {
    return t('Maps a feed element to the title, created date, published state or body of a node. Note that standard field mapping by FeedAPI still applies. For example if there is no feed element mapped to the node body you will still find the description in node body because that is how FeedAPI stores nodes.');
  }
  else if ($op == 'list') {
    return array('title' => t('Title'), 'created' => t('Published date'), 'body' => t('Body'), 'status' => t('Published state'));
  }
  else if ($op == 'map') {
    if (in_array($field_name, array('title', 'body', 'created'))) {
      if (is_string($feed_element) || is_numeric($feed_element)) {
        $node->{$field_name} = $feed_element;
      }
      return $node;
    }
    else if ($field_name == 'status') {
      if (isset($feed_element)) {
        $node->{$field_name} = empty($feed_element) ? 0 : 1;
      }
      return $node;
    }
  }
}

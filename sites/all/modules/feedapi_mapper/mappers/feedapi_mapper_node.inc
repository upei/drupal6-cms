<?php
// $Id: feedapi_mapper_node.inc,v 1.1.2.4 2009/04/20 13:31:04 alexb Exp $

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
    return t('Maps a feed element to a title, created date or a body of a node. Note that standard field mapping by FeedAPI still applies. For example if there is no feed element mapped to the node body you will still find the description in node body because that is how FeedAPI stores nodes.');
  }
  else if ($op == 'list') {
    return array('title' => t('Title'), 'created' => t('Published date'), 'body' => t('Body'));
  }
  else if ($op == 'map' && in_array($field_name, array('title', 'body', 'created'))) {
    if (is_string($feed_element) || is_numeric($feed_element)) {
      $node->{$field_name} = $feed_element;
    }
    return $node;
  }
}

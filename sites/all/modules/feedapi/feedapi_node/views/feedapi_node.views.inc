<?php
// $Id: feedapi_node.views.inc,v 1.1.2.2 2008/10/07 20:58:53 aronnovak Exp $

/**
 * @file
 * Add views functionality to FeedAPI Node
 *
 * Offer feed-related arguments
 */

/**
 * Implementation of hook_views_data().
 */
function feedapi_node_views_data() {
  $data['feedapi_node_item']['table']['group'] = t('FeedAPI Item');
  $data['feedapi_node_item_feed']['table']['group'] = t('FeedAPI Item');
  $data['feed_node']['table']['group'] = t('FeedAPI Parent Feed');
  $data['feedapi']['table']['group'] = t('FeedAPI Parent Feed');
  
  $data['feedapi_node_item']['table']['join']['node'] = array(
    'left_table' => 'feedapi_node_item_feed',
    'left_field' => 'feed_item_nid',
    'field' => 'nid',
  );
  $data['feedapi_node_item_feed']['table']['join']['node'] = array(
    'left_field' => 'nid',
    'field' => 'feed_item_nid',
  );
  $data['feedapi']['table']['join']['node'] = array(
    'left_table' => 'feedapi_node_item_feed',
    'left_field' => 'feed_nid',
    'field' => 'nid',
  );
  $data['feed_node']['table']['join']['node'] = array(
    'table' => 'node',
    'left_table' => 'feedapi_node_item_feed',
    'left_field' => 'feed_nid',
    'field' => 'nid',
  );
  
  // Item-related fields
  $data['feedapi_node_item']['url'] = array(
    'title' => t('URL'),
    'help' => t('The original URL of this feed item'),
    'field' => array(
      'handler' => 'views_handler_field_url',
    ),
  );
  $data['feedapi_node_item']['timestamp'] = array(
    'title' => t('Date'),
    'help' => t('The date of item publish'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
  );
  $data['feedapi_node_item']['item_title_url'] = array(
    'field' => 'url',
    'title' => t('Title with link to original URL'),
    'help' => t('Feed item title with link to original URL'),
    'field' => array(
      'handler' => 'feedapi_node_handler_feedapi_item_title_url',
      'click sortable' => TRUE,
    ),
  );
  
  // Feed-related fields
  $data['feed_node']['title'] = array(
    'title' => t('Title'),
    'help' => t('Title of the feed node where this item arrived'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
  );
  $data['feedapi']['checked'] = array(
    'title' => t('Last refresh'),
    'help' => t('The date when the parent feed was refreshed.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
    ),
  );
  $data['feedapi']['feed_url'] = array(
    'real field' => 'url',
    'title' => t('URL'),
    'help' => t('The source RSS/Atom/RDF feed URL'),
    'field' => array(
      'handler' => 'views_handler_field_url',
    ),
  );
  $data['feedapi']['feed_link1'] = array(
    'real field' => 'link',
    'title' => t('Link'),
    'help' => t('The original site'),
    'field' => array(
      'handler' => 'views_handler_field_url',
    ),
  );
  $data['feedapi']['guid'] = array(
    'real field' => 'title',
    'title' => t('Title with link to node'),
    'help' => t('Title of the feed node where this item arrived'),
    'field' => array(
      'handler' => 'feedapi_node_handler_feedapi_title_nid',
    ),
  );
  $data['feedapi']['url'] = array(
    'title' => t('Title with link to feed'),
    'help' => t('Title of the feed where this item arrived'),
    'field' => array(
      'handler' => 'feedapi_node_handler_feedapi_title_url',
    ),
  );
  $data['feedapi']['feed_link'] = array(
    'real field' => 'link',
    'title' => t('Title with link to site'),
    'help' => t('Title of the feed node where this item arrived'),
    'field' => array(
      'handler' => 'feedapi_node_handler_feedapi_title_link',
    ),
  );
  
  // Argument for filtering a specific feed
  $data['feedapi_node_item_feed']['feed_nid'] = array(
    'title' => t('Parent feed'),
    'help' => t('The feed that generated this node'),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );
  
  return $data;
}

/**
 * Implementation of hook_views_handlers().
 */
function feedapi_node_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'feedapi_node') . '/views/handlers',
    ),
    'handlers' => array(

      // field handlers
      'feedapi_node_handler_feedapi_title_nid' => array(
        'parent' => 'views_handler_field',
      ),
      'feedapi_node_handler_feedapi_title_url' => array(
        'parent' => 'views_handler_field',
      ),
      'feedapi_node_handler_feedapi_title_link' => array(
        'parent' => 'views_handler_field',
      ),
      'feedapi_node_handler_feedapi_item_title_url' => array(
        'parent' => 'views_handler_field',
      ),
    ),
  );
}

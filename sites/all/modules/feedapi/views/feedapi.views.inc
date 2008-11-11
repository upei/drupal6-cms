<?php
// $Id: feedapi.views.inc,v 1.1.2.2 2008/10/09 07:42:31 aronnovak Exp $

/**
 * @file
 * Add views functionality to FeedAPI Node
 *
 * Offer feed-related arguments
 */

/**
 * Implementation of hook_views_data().
 */
function feedapi_views_data() {
  $data['feedapi_standalone']['table']['group'] = t('FeedAPI Standalone Feed');
  
  $data['feedapi_standalone']['table']['join']['node'] = array(
    'table' => 'feedapi',
    'left_field' => 'nid',
    'field' => 'nid',
  );
  
  
  // Feed-related fields
  $data['feedapi_standalone']['checked'] = array(
    'title' => t('Last refresh'),
    'help' => t('The date when the parent feed was refreshed.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
    ),
  );
  $data['feedapi_standalone']['feed_url'] = array(
    'real field' => 'url',
    'title' => t('URL'),
    'help' => t('The source RSS/Atom/RDF feed URL'),
    'field' => array(
      'handler' => 'views_handler_field_url',
    ),
  );
  $data['feedapi_standalone']['feed_link1'] = array(
    'real field' => 'link',
    'title' => t('Link'),
    'help' => t('The original site'),
    'field' => array(
      'handler' => 'views_handler_field_url',
    ),
  );
  $data['feedapi_standalone']['guid'] = array(
    'real field' => 'title',
    'title' => t('Title with link to node'),
    'help' => t('Title of the feed node where this item arrived'),
    'field' => array(
      'handler' => 'feedapi_handler_feedapi_title_nid',
    ),
  );
  $data['feedapi_standalone']['url'] = array(
    'title' => t('Title with link to feed'),
    'help' => t('Title of the feed where this item arrived'),
    'field' => array(
      'handler' => 'feedapi_handler_feedapi_title_url',
    ),
  );
  $data['feedapi_standalone']['feed_link'] = array(
    'real field' => 'link',
    'title' => t('Title with link to site'),
    'help' => t('Title of the feed node where this item arrived'),
    'field' => array(
      'handler' => 'feedapi_handler_feedapi_title_link',
    ),
  );
  
  $data['feedapi_standalone']['url_unique'] = array(
    'field' => 'url',
    'title' => t('Unique URL'),
    'help' => t('The feed that generated this node'),
    'filter' => array(
      'handler' => 'feedapi_handler_filter_url_unique',
    ),
  );
  
  return $data;
}

/**
 * Implementation of hook_views_handlers().
 */
function feedapi_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'feedapi') . '/views/handlers',
    ),
    'handlers' => array(

      // field handlers
      'feedapi_handler_feedapi_title_nid' => array(
        'parent' => 'views_handler_field',
      ),
      'feedapi_handler_feedapi_title_url' => array(
        'parent' => 'views_handler_field',
      ),
      'feedapi_handler_feedapi_title_link' => array(
        'parent' => 'views_handler_field',
      ),
      
      // filter handlers
      'feedapi_handler_filter_url_unique' => array(
        'parent' => 'views_handler_filter',
      ),
    ),
  );
}

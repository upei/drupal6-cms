<?php

function views_ajax_endpoint_views_plugins() {
  return array(
    'display' => array(
      'ajax_page' => array(
        'title' => t('AJAX Endpoint'),
        'help' => t('Display the view as a AJAX page. Remember to proxy this path through if you are behind a firewall!'),
        'handler' => 'views_plugin_display_ajax_page',
        'parent' => 'page', // so it knows to load the page plugin .inc file
        'uses hook menu' => TRUE,
        'use ajax' => FALSE,
        'use pager' => FALSE,
        'accept attachments' => FALSE,
        'admin' => t('AJAX Endpoint'),
      ),
    ),
    'style' => array(
      'views_ajax_json' => array(
        'title' => t('AJAX JSON Endpoint'),
        'theme' => 'views_view_ajax_json',
        'help' => t('Displays nodes in the JSON data format'),
        'handler' => 'views_plugin_style_ajax_json',
        'uses row plugin' => true,
        'uses fields' => true,
        'type' => 'ajax',
      ),
      
      'views_ajax_html' => array(
        'title' => t('AJAX HTML Endpoint'),
        'theme' => 'views_view_ajax_html',
        'help' => t('Displays nodes in HTML format'),
        'handler' => 'views_plugin_style_ajax_html',
        'uses row plugin' => true,
        'uses fields' => true,
		'uses options' => true,
        'type' => 'ajax',
      ),
    ),
    
    'row' => array(
      'serialized' => array(
        'title' => t('Serialized'),
        'handler' => 'views_plugin_row_serialized',
        'uses fields' => true,
        'type' => 'ajax',
      ),
    ),
  );
}

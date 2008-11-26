<?php

function views_ajax_endpoint_views_plugins() {
  return array(
    'style' => array(
      'views_ajax_json' => array(
        'title' => t('AJAX JSON Endpoint'),
        'theme' => 'views_view_ajax_json',
        'help' => t('Displays nodes in the JSON data format'),
        'handler' => 'views_plugin_style_ajax_json',
        'uses row plugin' => true,
        'uses fields' => true,
        'type' => 'normal',
      ),
      
      'views_ajax_html' => array(
        'title' => t('AJAX HTML Endpoint'),
        'theme' => 'views_view_ajax_html',
        'help' => t('Displays nodes in HTML format'),
        'handler' => 'views_plugin_style_ajax_html',
        'uses row plugin' => true,
        'uses fields' => true,
        'type' => 'normal',
      ),
    ),
    
    'row' => array(
      'serialized' => array(
        'title' => t('Serialized'),
        'handler' => 'views_plugin_row_serialized',
        'uses fields' => true,
        'type' => 'normal',
      ),
    ),
  );
}

<?php

function xmlsync_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'xmlsync') . '/handlers',
    ),
    'handlers' => array(
      'xmlsync_views_handler_field_xml' => array(
        'parent' => 'views_handler_field',
      ),
      'xmlsync_views_handler_filter_xml' => array(
        'parent' => 'views_handler_filter',
      ),
      'xmlsync_views_handler_sort_xml' => array(
        'parent' => 'views_handler_sort',
      ),
      'xmlsync_views_handler_argument_xml' => array(
        'parent' => 'views_handler_argument_string',
      ),
    ),
  );
}

function xmlsync_views_data() {
  $data['xmlsync']['table']['group'] = t('XML Sync');
  $data['xmlsync']['table']['join'] = array(
    'node' => array(
      'left_field' => 'nid',
      'field' => 'nid',
    ),
  );
  $data['xmlsync']['nid'] = array(
     'title' => t('Nid'),
     'help' => t('XML Sync content that references a node.'),
     'relationship' => array(
       'base' => 'node',
       'field' => 'nid',
       'handler' => 'views_handler_relationship',
       'label' => t('XML Sync'),
     ),
  );
  $data['xmlsync']['xmltype'] = array(
    'title' => t('Type'),
    'help' => t('XML type'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => FALSE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
  );
  $data['xmlsync']['url'] = array(
    'title' => t('URL'),
    'help' => t('URL to XML'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
  );

  $data['xmlsync']['last_sync'] = array(
    'title' => t('Last synchronized time'),
    'help' => t('Time for the last synchronization.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );

  $data['xmlsync_entities']['table']['group'] = t('XML Sync Entity');
  $data['xmlsync_entities']['table']['join'] = array(
    'node' => array(
      'left_field' => 'vid',
      'field' => 'vid',
    ),
  );
  $data['xmlsync_entities']['vid'] = array(
    'title' => t('XML sync entities'),
    'help' => t('XML sync entities that references a node.'),
    'relationship' => array(
      'base' => 'node',
      'field' => 'vid',
      'handler' => 'views_handler_relationship',
      'label' => t('XML sync entities'),
    ),
  );
  $data['xmlsync_entities']['data'] = array(
    'title' => t('Data'),
    'help' => t('An entity of XML sync'),
    'field' => array(
      'handler' => 'xmlsync_views_handler_field_xml',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'xmlsync_views_handler_filter_xml',
    ),
    'sort' => array(
      'handler' => 'xmlsync_views_handler_sort_xml',
    ),
    'argument' => array(
      'handler' => 'xmlsync_views_handler_argument_xml',
    ),
  );
  return $data;
}

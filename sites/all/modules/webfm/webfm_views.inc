<?php
// $Id: webfm_views.inc,v 1.8 2008/04/08 06:28:14 andremolnar Exp $

function webfm_views_tables(){
  $tables = array();

  /**
  * The webfm_attach table links directly to the node table,
  * via the nid field
  */
  $tables['webfm_attach'] = array('name' => 'webfm_attach',
                                  'join' => array(
                                    'type' => 'inner',
                                    'left' => array(
                                      'table' => 'node',
                                      'field' => 'nid'),
                                    'right' => array(
                                      'field' => 'nid')),
                                 );
  $tables['webfm_file'] = array('name' => 'webfm_file',
                                'join' => array(
                                  'type' => 'inner',
                                  'left' => array(
                                    'table' => 'webfm_attach',
                                    'field' => 'fid'),
                                  'right' => array(
                                    'table' => 'webfm_file',
                                    'field' => 'fid')),
                                 'fields' => array(
                                   'all_files' => array(
                                     'name' => t('WebFM: All files by name/title.'),
                                     'notafield' => true,
                                     'handler' => 'webfm_views_handler_file_all_files',
                                      'option' => array(
                                        '#type' => 'select',
                                        '#options' => array(
                                          'link' => t('With links'),
                                          'nolink' => t('Without links'))),
                                      'sortable' => false,
                                      'help' => t('Display ALL the files that have been attached to the node via WebFM. Metadata title is used where present when \'Display metadata title\' checked in settings.')),
                                    'fpath' => array(
                                      'name' => t('WebFM: File name'),
                                      'handler' => array (
                                        'webfm_views_handler_file_filename_download' => t('With links'),
                                        'webfm_views_handler_file_filename' => t('Without links')),
                                      'sortable' => true,
                                      // consider 'option' --> link inline - or link force download - extra arg for webfm send
                                      'addlfields' => array('fid'),
                                      'help' => t('Display the name of files that have been attached to a node via WebFM (with or without links to the files themselves)')),
                                    'fsize' => array(
                                      'name' => t('WebFM: File size'),
                                      'sortable' => true,
                                      'handler' => 'webfm_views_handler_file_size',
                                      'help' => t('Display the file size of files that have been attached to a node via WebFM')),
                                    'fmime' => array(
                                      'name' => t('WebFM: File mime type'),
                                      'sortable' => true,
                                      'help' => t('Display the file mime type of files that have been attached to a node via WebFM')),
                                    'ftitle' => array(
                                      'name' => t('WebFM metadata:  File title'),
 				                              'handler' => array (
 					                               'webfm_views_handler_file_meta_download' => t('With links'),
 					                               'webfm_views_handler_file_meta' => t('Without links')),
                                      'sortable' => true,
 				                              'addlfields' => array('fid'),
                                      'help' => t('Display the file title of files that have been attached to a node via WebFM (with or without links to the files themselves)')),
                                    'fdesc' => array(
                                      'name' => t('WebFM metadata:  File description'),
                                      'sortable' => true,
                                      'handler' => 'webfm_views_handler_file_meta',
                                      'help' => t('Display the description of files that have been attached to a node via WebFM')),
                                    'flang' => array(
                                      'name' => t('WebFM metadata:  File language'),
                                      'sortable' => true,
                                      'handler' => 'webfm_views_handler_file_meta',
                                      'help' => t('Display the language of files that have been attached to a node via WebFM')),
                                    'fpublisher' => array(
                                      'name' => t('WebFM metadata:  File publisher'),
                                      'sortable' => true,
                                      'handler' => 'webfm_views_handler_file_meta',
                                      'help' => t('Display the publisher of files that have been attached to a node via WebFM')),
                                    'dl_cnt' => array(
                                      'name' => t('WebFM:  Download Count'),
                                      'sortable' => true,
                                      'help' => t('Display the number of times a file has been downloaded via WebFM'))),
                                  'filters' => array(
                                    'fpath' => array(
                                      'name' => t('WebFM: File name'),
                                      'operator' => 'views_handler_operator_like',
                                      'handler' => 'views_handler_filter_like',
                                      'help' => t('Filter nodes by the names of files that have been attached via WebFM.  e.g. show only nodes with a file called "foo.txt" attached to them')),
                                    'fsize' => array(
                                      'name' => t('WebFM: File size'),
                                      'operator' => 'views_handler_operator_gtlt',
                                      'help' => t('Filter nodes by the size of files that have been attached via WebFM. e.g. show only nodes with files larger than 1M attached to them')),
                                    'fmime' => array(
                                      'name' => t('WebFM: File mime type'),
                                      'operator' => 'views_handler_operator_like',
                                      'handler' => 'views_handler_filter_like',
                                      'help' => t('Filter nodes by the mime type of files that have been attached via WebFM.  e.g. show only nodes with a .pdf document attached to them')),
                                    'ftitle' => array(
                                      'name' => t('WebFM metadata: File title'),
                                      'operator' => 'views_handler_operator_like',
                                      'handler' => 'views_handler_filter_like',
                                      'help' => t('Filter nodes by the title of files that have been attached via WebFM.  e.g. show only nodes with a file attached wich has a metadata title like "bar"')),
                                    'fdesc' => array(
                                      'name' => t('WebFM metadata: File description'),
                                      'operator' => 'views_handler_operator_like',
                                      'handler' => 'views_handler_filter_like',
                                      'help' => t('Filter nodes by the description of files that have been attached via WebFM.  e.g. show only nodes with a file attached which have a metadata description which contains all the words "foo, bar and baz"')),
                                    'flang' => array(
                                      'name' => t('WebFM metadata: File language'),
                                      'operator' => 'views_handler_operator_like',
                                      'handler' => 'views_handler_filter_like',
                                      'help' => t('Filter nodes by the language of files that have been attached via WebFM.  e.g. show only nodes with a file attached which have a metadata language equal to "fr"')),
                                    'fpublisher' => array(
                                      'name' => t('WebFM metadata: Sort by file publisher'),
                                      'operator' => 'views_handler_operator_like',
                                      'handler' => 'views_handler_filter_like',
                                      'help' => t('Filter nodes by publisher of files that have been attached via WebFM.')),
                                    'dl_cnt' => array(
                                      'name' => t('WebFM:  Download Count'),
                                      'operator' => 'views_handler_operator_like',
                                      'handler' => 'views_handler_filter_like',
                                      'help' => t('Filter nodes by downloaded count of files that have been attached via WebFM.'))),
                                  'sorts' => array(
                                    'fpath' => array(
                                      'name' => t('WebFM: Sort by file name'),
                                      'help' => t('Sort by file name')),
                                    'fsize' => array(
                                      'name' => t('WebFM: Sort by file size'),
                                      'help' => t('Sort by file size.')),
                                    'fmime' => array(
                                      'name' => t('WebFM: Sort by mime type'),
                                      'help' => t('Sort by mime type.')),
                                    'ftitle' => array(
                                      'name' => t('WebFM metadata: Sort by file title'),
                                      'help' => t('Sort by file metadata title')),
                                    'flang' => array(
                                      'name' => t('WebFM metadata: Sort by file language'),
                                      'help' => t('Sort by file language.')),
                                    'fpublisher' => array(
                                      'name' => t('WebFM metadata: Sort by file publisher'),
                                      'help' => t('Sort by file publisher.')),
                                    'dl_cnt' => array(
                                      'name' => t('WebFM: Download Count'),
                                      'help' => t('Sort by file downloaded count')))
                                );
  return $tables;
}

function webfm_views_handler_file_all_files($fieldinfo, $fielddata, $value, $data){
  $links = array();

  $query = "SELECT wf.* FROM {webfm_file} wf INNER JOIN {webfm_attach} wa ON wf.fid = wa.fid WHERE wa.nid = %d ORDER BY %s";
  $result = db_query($query, $data->nid, 'wa.weight');
  while ($file = db_fetch_object($result)) {
    if(variable_get('webfm_display_title', '') && $file->ftitle) {
      $fname = urldecode($file->ftitle);
    } else {
      $fname = strrev(substr(strrev($file->fpath), 0, strpos(strrev($file->fpath), '/')));
    }
    if ($fielddata['options'] == 'nolink') {
      $links[] = check_plain($fname);
    } else {
      $links[] = l(check_plain($fname), 'webfm_send/'.$file->fid);
    }
  }
  return implode(' | ', $links);
}

function webfm_views_handler_file_filename($fieldinfo, $fielddata, $value, $data){
  $name = strrev(substr(strrev($value), 0, strpos(strrev($value), '/')));
  return $name;
}

function webfm_views_handler_file_filename_download($fieldinfo, $fielddata, $value, $data){
  $name = strrev(substr(strrev($value), 0, strpos(strrev($value), '/')));
  return l(check_plain($name), 'webfm_send/'.$data->webfm_file_fid);
}

function webfm_views_handler_file_size($fieldinfo, $fielddata, $value, $data){
  return format_size($value);
}

function webfm_views_handler_file_meta($fieldinfo, $fielddata, $value, $data) {
  return rawurldecode($value);
}

function webfm_views_handler_file_meta_download($fieldinfo, $fielddata, $value, $data){
  return l(check_plain(rawurldecode($value)), 'webfm_send/'.$data->webfm_file_fid);
}

function webfm_views_default_views(){
}

<?php

// $Id$

function xmlsync_cleanstring($s, $clean_slash = TRUE) {
  if (function_exists('_pathauto_include'))
    _pathauto_include();

  if (function_exists('transliterate_get')) {
    return strtolower(transliterate_get($s));
  }
  else if (function_exists('pathauto_cleanstring')) {
    return strtolower(pathauto_cleanstring($s, $clean_slash));
  }
  else {
    $s = preg_replace(
      array(
        '# #',
        '#[^/A-Za-z0-9_-]#',
      ),
      array(
        '_',
        '',
      ),
      $s
    );
    if ($clean_slash) {
      $s = preg_replace('#/#', '-', $s);
    }
    return strtolower($s);
  }
}

function _xmlsync_create_alias($node, $record) {
  // get the doc data
  $doc = simplexml_load_string($record->data);
  // grep all replacements in the node
  if(preg_match_all('#(\[([^\]]+)\])#u', $node->record_alias_template, $matches)) {
    $patterns = $matches[1];
    $xpaths = $matches[2];
    $replacments = array();
    // get the result
    foreach($xpaths as $xpath) {
      $s = strval(array_pop($doc->xpath($xpath)));
      // check NULL if needed
      if (NULL == $s) $s = '';
      // update replacement patterns
      $replacements[] = xmlsync_cleanstring($s);
    }
  }
  // replace token patterns, clean the alias up, and trim opening and ending slashes
  $alias = preg_replace('#(^/+|/+$)#', '',
    xmlsync_cleanstring(
      str_replace($patterns, $replacements, $node->record_alias_template),
      FALSE)
    );

  // lookup the path to check if it exists
  if (drupal_lookup_path('source', $alias)) {
    $index = 0;
    while (drupal_lookup_path('source', $alias . '-' . ++$index)) ;
    $alias = $alias . '-' . $index;
  }
  path_set_alias('xmlsync/record/' . $record->xid, $alias);
}

function _xmlsync_update_url_content(&$node) {
  if ($node->xmltype != 'url') {
    return;
  }
  $ret = drupal_http_request($node->url);
  if ($ret->error) {
    form_set_error('url', $ret->error);
  }
  else {
    $node->body = $ret->data;
    $node->last_sync = time();
  }
}

function _xmlsync_extract_content(&$node) {
  // load simple xml element
  $doc = simplexml_load_string($node->body);
  if (!$doc) {
    form_set_error('body', t('XML content is not well-formed.'));
    return;
  }

  $feed = array_pop($doc->xpath('/feed'));
  $attr = $feed->attributes();
  // update title if no title is provided
  if (empty($node->title)) {
    if ($feed) {
      $title = $attr['title'];
    }
    if (empty($title)) {
      $title = t('XMLSync feed');
    }
    $node->title = $title;
  }
  $node->xml_title = $attr['title'];
  $node->xml_description = $attr['description'];
  $node->entity_count = $attr['total'];
  
  // get all indexes
  $keys = $doc->xpath('/feed/indexes/key');
  $keys = array_map('strval', $keys);
  
  $node->entities = array();  
  // load all xml entities
  foreach ($doc->xpath('/feed/node') as $key => $entity) {
    $rec = new stdclass();
    $rec->nid = $node->nid;
    $rec->vid = $node->vid;
    foreach ($keys as $id => $key) {
      $name = 'index' . $id . '_name';
      $value = 'index' . $id . '_value';
      $rec->$name = $key;
      $rec->$value = strval(array_pop($entity->xpath("$key")));
    }
    $rec->data = $entity->data->asXML();
    // grab attributes
    $attr = $entity->attributes();
    $rec->entity_id = $attr['id'];
    $rec->entity_title = $attr['title'];
    $rec->entity_description = $attr['description'];
    // add the record to node
    $node->entities[] = $rec;
  }
}

function _xmlsync_delete_aliases($node) {
  // remove all xmlsync record alias
  // get all xid
  $result = db_query(db_rewrite_sql('SELECT xid FROM {xmlsync_entities} WHERE nid=%d'), $node->nid);
  while ($record = db_fetch_object($result)) {
    path_set_alias('xmlsync/record/' . $record->xid);
  }
  unset($result);
}

function _xmlsync_record_page_get_title($xid = NULL) {
  if (!$xid) {
    $menu_item = menu_get_item();
    $xid = $menu_item['page_arguments'][0];
  }

  // get the record
  $record = db_fetch_object(db_query(db_rewrite_sql('SELECT * FROM {xmlsync_entities} WHERE xid=%d'), $xid));
  if ($record) {
    return check_plain($record->entity_title);
  }
}

function _xmlsync_record_page_get_node($xid = NULL) {
  if (!$xid) {
    $menu_item = menu_get_item();
    $xid = $menu_item['page_arguments'][0];
  }
  
  $record = db_fetch_object(db_query(db_rewrite_sql('SELECT nid FROM {xmlsync_entities} WHERE xid=%d'), $xid));
  if ($record) {
    return node_load($record->nid);
  }
  else {
    return FALSE;
  }
}


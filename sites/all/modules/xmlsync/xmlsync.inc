<?php

// $Id: xmlsync.inc,v 1.2 2009/10/16 18:58:09 gzfelix Exp $

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
  $body = preg_replace('/xmlns="[^"]+"/', '', $record->data);
  $doc = new DOMDocument();
  if (!$doc->loadXML($body)) {
    drupal_set_message(t('Unable to parse record.'));
    return;
  }
  $x = new DOMXPath($doc);
  
  // grep all replacements in the node
  if(preg_match_all('#(\[([^\]]+)\])#u', $node->record_alias_template, $matches)) {
    $patterns = $matches[1];
    $xpaths = $matches[2];
    $replacments = array();
    // get the result
    foreach($xpaths as $xpath) {
      // get the node value
      foreach ($x->query($xpath) as $e) {
        $s = $e->nodeValue;
        break;
      }
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
  $body = preg_replace('/xmlns="[^"]+"/', '', $node->body);
  $doc = new DOMDocument();
  if (!$doc->loadXML($body)) {
    form_set_error('body', t('XML content is not well-formed.'));
    return;
  }
  
  $xpath = new DOMXPath($doc);
  
  // get the feed
  $feed = NULL;
  foreach ($xpath->query($node->root_xpath) as $e) {
    $feed = $e;
    break;
  }
  // update title if no title is provided
  foreach ($xpath->query($node->document_title_xpath) as $e) {
    $node->xml_title = $e->nodeValue;
    break;
  }

  if (empty($node->title)) {
    $node->title = $node->xml_title;
    if (empty($title)) {
      $title = t('XMLSync feed');
    }
    $node->title = $title;
  }

  // description
  foreach ($xpath->query($node->document_description_xpath) as $e) {
    $node->xml_description = $e->nodeValue;
  }
  // entity count
  $node->entity_count = $xpath->evaluate('count(' . $node->record_xpath . ')');
  
  // load all xml entities
  $node->entities = array();
  foreach ($xpath->query($node->record_xpath) as $entity) {
    $rec = new stdclass();
    $rec->nid = $node->nid;
    $rec->vid = $node->vid;
    $rec->data = $doc->saveXML($entity);
    // grab attributes
    // id
    foreach ($xpath->query($node->record_id_xpath, $entity) as $e) {
      $rec->entity_id = $e->nodeValue;
      break;
    }
    // title
    foreach ($xpath->query($node->record_title_xpath, $entity) as $e) {
      $rec->entity_title = $e->nodeValue;
      break;
    }
    // description
    foreach ($xpath->query($node->record_description_xpath, $entity) as $e) {
      $rec->entity_description = $e->nodeValue;
      break;
    }
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
    return check_markup(html_entity_decode($record->entity_title));
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


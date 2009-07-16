<?php

function xmlsync_record_view($xid) {
  // load node 
  $record = db_fetch_object(db_query(db_rewrite_sql('SELECT * FROM {xmlsync_entities} WHERE xid=%d'), $xid));
  if ($record) {
    // load the related node
    $node = node_load($record->nid);
    // set the path alias
    $record->path_alias = drupal_get_path_alias("xmlsync/record/{$record->xid}");
    return theme('xmlsync_record', $node, $record);
  }
  else {
    drupal_not_found();
  }
}


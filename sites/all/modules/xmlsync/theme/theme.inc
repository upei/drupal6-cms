<?php

// $Id: theme.inc,v 1.1 2009/07/17 14:28:10 gzfelix Exp $

function template_preprocess_xmlsync_record(&$vars) {
  // enable simplexml object
  $vars['data'] = simplexml_load_string($vars['record']->data);
  
  if ($vars['node']->record_template_name) {
    $vars['template_files'][] = 'xmlsync-record--' . $vars['node']->record_template_name;
  }

  // template files
  function x ($data, $path) {
    return strval(array_pop($data->xpath($path)));
  }

  // get record ref
  $record =& $vars['record'];

  // safety cleanup
  $record->entity_id = check_plain($record->entity_id);
  $record->entity_title = check_plain($record->entity_title);
  $record->entity_description = check_plain($record->entity_description);
  $record->data = check_markup($record->data);
}


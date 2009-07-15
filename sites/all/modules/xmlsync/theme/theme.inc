<?php

function template_preprocess_xmlsync_record(&$vars) {
  // template files
  $vars['template files'][] = 'xmlsync-record';
  if ($vars['node']->record_template_name) {
    $vars['template files'][] = 'xmlsync-record--' . $vars['node']->record_template_name;
  }
  // enable simplexml object
  $vars['data'] = simplexml_load_string($vars['record']->data);
}

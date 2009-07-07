<?php

class xmlsync_views_handler_field_data extends views_handler_field {

  function ui_name() {
    if ($this->broken()) {
      return t('Broken field data. Unsupported database type.');
    }
    else {
      return parent::ui_name();
    }
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['xpath'] = '.';
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form(&$form, &$form_state);
    $form['xpath'] = array(
      '#type' => 'textfield',
      '#title' => 'XPath query',
      '#default_value' => $this->options['xpath'],
    );
  }

  function render($values) {
    $data = $values->{$this->field_alias};
    if ($data) {
      $doc = simplexml_load_string($data);
      $ret = $doc->xpath($this->options['xpath']);
      if ($ret[0]) {
        return strval($ret[0]);
      }
    }
  }

  function broken() {
    global $db_type;
    switch ($db_type) {
    case 'mysql':
    case 'mysqli':
      return FALSE;
    default:
      return TRUE;
    }
  }
}

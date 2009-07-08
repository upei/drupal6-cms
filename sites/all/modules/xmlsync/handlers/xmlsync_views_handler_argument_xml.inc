<?php

class xmlsync_views_handler_argument_xml extends views_handler_argument_string {

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

  function ui_name($short = FALSE) {                                                                                                                       
    if ($this->broken()) {
      return t('Broken field data. Unsupported database type.');
    }   
    else {
      return parent::ui_name($short) . t(': !xpath', array('!xpath' => $this->options['xpath']));
    }   
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['xpath'] = array('default' => '.');
    $options['operator'] = array('default' => 'op_starts');
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['xpath'] = array(
      '#type' => 'textfield',
      '#title' => t('XPath query'),
      '#default_value' => $this->options['xpath'],
      '#weight' => -5,
    );
    $form['operator'] = array(
      '#type' => 'select',
      '#title' => t('Operator'),
      '#default_value' => $this->options['operator'],
      '#weight' => -3,
      '#options' => array(
        'op_starts' => t('Starts with'),
        'op_ends' => t('Ends with'),
        'op_contains' => t('Contains'),
        'op_equals' => t('Is equal to'),
        'op_not_equals' => t('Is not equal to'),
      ),
    );
    unset($form['glossary']);
  }

  function query() {
    $argument = $this->argument;
    if (!empty($this->options['transform_dash'])) {
      $argument = strtr($argument, '-', ' ');
    }
    
    $this->ensure_my_table();
    $field = "$this->table_alias.$this->real_field";

    if (empty($this->options['operator'])) {
      op_equal($field, $this->options['xpath'], $argument);
    }
    else {
      $this->{$this->options['operator']}($field, $this->options['xpath'], $argument);
    }
  }

  function op_equals($field, $xpath, $argument) {
    $this->query->add_where(0, "EXTRACTVALUE(%s, '%s') = '%s'", $field, $xpath, $argument);
  }

  function op_not_equals($field, $xpath, $argument) {
    $this->query->add_where(0, "EXTRACTVALUE(%s, '%s') != '%s'", $field, $xpath, $argument);
  }

  function op_starts($field, $xpath, $argument) {
    $this->query->add_where(0, "EXTRACTVALUE(%s, '%s') LIKE '%s%%'", $field, $xpath, $argument);
  }

  function op_ends($field, $xpath, $argument) {
    $this->query->add_where(0, "EXTRACTVALUE(%s, '%s') LIKE '%%%s'", $field, $xpath, $argument);
  }

  function op_contains($field, $xpath, $argument) {
    $this->query->add_where(0, "EXTRACTVALUE(%s, '%s') LIKE '%%%s%%'", $field, $xpath, $argument);
  }
}

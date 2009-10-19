<?php

// $Id: xmlsync_views_handler_argument_xml.inc,v 1.2.2.1 2009/10/16 19:06:25 gzfelix Exp $

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
      return parent::ui_name($short) . t(': !xpath', array('!xpath' => filter_xss_admin($this->options['xpath'])));
    }   
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['xpath'] = array('default' => '.');
    $options['operator'] = array('default' => 'op_starts');
    $options['multiple'] = array('default' => FALSE);
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['xpath'] = array(
      '#type' => 'textfield',
      '#title' => t('XPath query'),
      '#default_value' => $this->options['xpath'],
    );
    $form['operator'] = array(
      '#type' => 'select',
      '#title' => t('Operator'),
      '#default_value' => $this->options['operator'],
      '#options' => array(
        'op_starts' => t('Starts with'),
        'op_ends' => t('Ends with'),
        'op_contains' => t('Contains'),
        'op_equals' => t('Is equal to'),
        'op_not_equals' => t('Is not equal to'),
        'op_ignore' => t('Just ignore it'),
      ),
    );
    $form['multiple'] = array(
      '#type' => 'checkbox',
      '#title' => t('Handle multiple arguments'),
      '#description' => t('Multiple arguments can be separated by comma'),
      '#default_value' => $this->options['multiple'],
    );
    unset($form['glossary']);
  }

  function query() {
    $arguments = $this->argument;
   
    $this->ensure_my_table();
    $field = "$this->table_alias.$this->real_field";

    // supports multiple arguments
    if (!empty($this->options['multiple'])) {
      $arguments = preg_split('/\s*,\s*/', $arguments);
      $group = $this->query->set_where_group('OR');
    }
    else {
      $arguments = array($arguments);
      $group = 0;
    }
    foreach ($arguments as $id => $argument) {
      if (!empty($this->options['transform_dash'])) {
        $argument = strtr($argument, '-', ' ');
      }
      if (empty($this->options['operator'])) {
        op_equal($group, $field, filter_xss_admin($this->options['xpath']), $argument);
      }
      else {
        $this->{$this->options['operator']}($group, $field, filter_xss_admin($this->options['xpath']), $argument);
      }
    }
  }

  function op_equals($group, $field, $xpath, $argument) {
    $this->query->add_where($group, "EXTRACTVALUE(%s, '%s') = '%s'", $field, $xpath, $argument);
  }

  function op_not_equals($group, $field, $xpath, $argument) {
    $this->query->add_where($group, "EXTRACTVALUE(%s, '%s') != '%s'", $field, $xpath, $argument);
  }

  function op_starts($group, $field, $xpath, $argument) {
    $this->query->add_where($group, "EXTRACTVALUE(%s, '%s') LIKE '%s%%'", $field, $xpath, $argument);
  }

  function op_ends($group, $field, $xpath, $argument) {
    $this->query->add_where($group, "EXTRACTVALUE(%s, '%s') LIKE '%%%s'", $field, $xpath, $argument);
  }

  function op_contains($group, $field, $xpath, $argument) {
    $this->query->add_where($group, "EXTRACTVALUE(%s, '%s') LIKE '%%%s%%'", $field, $xpath, $argument);
  }

  function op_ignore($group, $field, $xpath, $argument) {
    $this->query->add_where($group, "1");
  }
}

<?php

// $Id: xmlsync_views_handler_field_xml.inc,v 1.2.2.1 2009/10/16 19:06:25 gzfelix Exp $

class xmlsync_views_handler_field_xml extends views_handler_field {

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
    $options['distinct'] = array('default' => '');
    $options['record_link'] = array('default' => '');
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form(&$form, &$form_state);
    $form['xpath'] = array(
      '#type' => 'textfield',
      '#title' => t('XPath query'),
      '#default_value' => $this->options['xpath'],
    );
    $form['record_link'] = array(
      '#type' => 'checkbox',
      '#title' => t('Link to the record'),
      '#default_value' => $this->options['record_link'],
    );
    $form['distinct'] = array(
      '#type' => 'checkbox',
      '#title' => t('Distinct result'),
      '#description' => t('Show distinct result'),
      '#default_value' => $this->options['distinct'],
    );
  }

  function pre_query() {
    // distinct
    $this->ensure_my_table();
    $this->field_alias = $this->table_alias . '_' . $this->real_field . '_' . 
    preg_replace(
      array(
        '#[^A-Za-z0-9/-]#',
        '#[/-]#',
      ),
      array(
        '',
        '_',
      ),
      filter_xss_admin($this->options['xpath'])
    );
  }

  function query() {
    $xpath = filter_xss_admin($this->options['xpath']);
    $this->ensure_my_table();
    $this->query->fields[$this->field_alias] = array(
      'field' => "EXTRACTVALUE($this->table_alias.$this->real_field, '$xpath')",
      'table' => NULL,
      'alias' => $this->field_alias,
    );
    // check distinct support
    if (!empty($this->options['distinct'])) {
      $this->query->add_groupby($this->field_alias);
    }
    // chec record link
    if (!empty($this->options['record_link'])) {
      $this->query->add_field(NULL, 'xid');
    }
  }

  function render($values) {
    if (empty($this->options['record_link'])) {
      return html_entity_decode($values->{$this->field_alias});
    }
    else {
      return l(html_entity_decode($values->{$this->field_alias}), drupal_get_path_alias('xmlsync/record/'.$values->xid));
    }
  }

  function get_render_tokens() {
    $tokens = parent::get_render_tokens();

    foreach ($this->view->display_handler->get_handlers('field') as $field => $handler) {
      if (isset($handler->last_render)) {                                                                                   
        $tokens["[{$field}-lower]"] = strtolower($handler->last_render);
        $tokens["[{$field}-url]"] = preg_replace(
          array(
            '/ /',
          ),
          array(
            '+',
          ),
          strtolower($handler->last_render)
        );

      }   
      // We only use fields up to (and including) this one.
      if ($field == $this->options['id']) {
        break;
      }   
    }

   return $tokens; 
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

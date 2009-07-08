<?php

class xmlsync_views_handler_field_xml extends views_handler_field {

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
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form(&$form, &$form_state);
    $form['xpath'] = array(
      '#type' => 'textfield',
      '#title' => 'XPath query',
      '#default_value' => $this->options['xpath'],
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
      $this->options['xpath']
    );
  }

  function query() {
    $this->ensure_my_table();
    $this->query->fields[$this->field_alias] = array(
      'field' => "EXTRACTVALUE($this->table_alias.$this->real_field, '{$this->options['xpath']}')",
      'table' => NULL,
      'alias' => $this->field_alias,
    );
    // check distinct support
    if (!empty($this->options['distinct'])) {
      $this->query->add_groupby($this->field_alias);
    }
  }

  function render($values) {
    return $values->{$this->field_alias};
  }

  function get_render_tokens() {
    $tokens = parent::get_render_tokens();

    foreach ($this->view->display_handler->get_handlers('field') as $field => $handler) {
      if (isset($handler->last_render)) {                                                                                   
        $tokens["[{$field}-path]"] = preg_replace(
          array(
            //'/ /',
          ),
          array(
            //'+',
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

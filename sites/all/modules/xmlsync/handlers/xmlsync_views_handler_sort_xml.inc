<?php

class xmlsync_views_handler_sort_xml extends views_handler_sort {

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
    $options['cast_as'] = array('default' => 'CHAR');
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
    $form['cast_as'] = array(
      '#type' => 'select',
      '#title' => t('Cast as'),
      '#default_value' => $this->options['cast_as'],
      '#options' => array(
        'BINARY' => t('Binary'),
        'CHAR' => t('Char'),
        'SIGNED' => t('Signed Integer'),
        'UNSIGNED' => t('Unsigned Integer'),
      ),
      '#weight' => -3,
    );
  }

  function query() {
    $this->ensure_my_table();
    $field = "$this->table_alias.$this->real_field";
    
    // FIXME hack views_query->orderby[] directly instead of using views_query->add_orderby
    //       because views_query does not handle formulas very well.
    //       needs to use _db_query_callback to encode parameters correctly.
    $query = "CAST(EXTRACTVALUE(%s, '%s') AS %s)";
    $args = array($field, filter_xss_admin($this->options['xpath']), $this->options['cast_as']);
    _db_query_callback($args, TRUE);
    $query = preg_replace_callback(DB_QUERY_REGEXP, '_db_query_callback', $query);
    $this->query->orderby[] = "$query " . strtoupper($this->options['order']);
  }

}

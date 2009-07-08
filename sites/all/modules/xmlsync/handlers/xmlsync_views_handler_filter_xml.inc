<?php

class xmlsync_views_handler_filter_xml extends views_handler_filter {

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

  function can_expose() {
    return FALSE;
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['xpath'] = array('default' => '.');
    $options['cast_as'] = array('default' => 'CHAR');
    $options['case'] = array('default' => TRUE);
    return $options;
  }

  function operators() {
    $operators = array(
      '=' => array(
        'title' => t('Is equal to'),
        'short' => t('='),
        'method' => 'op_equal',
        'values' => 1,
      ),
      '!=' => array(
        'title' => t('Is not equal to'),
        'short' => t('!='),
        'method' => 'op_equal',
        'values' => 1,
      ),
      '<' => array(
        'title' =>  t('Less than'),
        'short' => t('<'),
        'method' => 'op_equal',
        'values' => 1,
      ),
      '<=' => array(
        'title' => t('Less than or equal to'),
        'short' => t('<='),
        'method' => 'op_equal',
        'values' => 1,
      ),
      '>' => array(
        'title' => t('Greater than'),
        'short' => t('>'),
        'method' => 'op_equal',
        'values' => 1,
      ),
      '>=' => array(
        'title' => t('Greater than or equal to'),
        'short' => t('>='),
        'method' => 'op_equal',
        'values' => 1,
      ),
      'contains' => array(
        'title' => t('Contains'),
        'short' => t('contains'),
        'method' => 'op_contains',
        'values' => 1,
      ),
      'starts' => array(
        'title' => t('Starts with'),
        'short' => t('begins'),
        'method' => 'op_starts',
        'values' => 1,
      ),
      'ends' => array(
        'title' => t('Ends with'),
        'short' => t('ends'),
        'method' => 'op_ends',
        'values' => 1,
      ),
      'REGEXP' => array(
        'title' => t('Matches regular expression'),
        'short' => t('regexp'),
        'method' => 'op_regexp',
        'values' => 1,
      ),
      'NOT REGEXP' => array(
        'title' => t('Not matches regular expression'),
        'short' => t('!regexp'),
        'method' => 'op_regexp',
        'values' => 1,
      ),
    );

    return $operators;
  }

  function operator_options($which = 'title') {
    $options = array();
    foreach ($this->operators() as $id => $info) {
      $options[$id] = $info[$which];
    }
    return $options;
  }

  function value_form(&$form, &$form_state) {
    parent::value_form($form, $form_state);
    $form['value'] = array(
      '#type' => 'textfield',
      '#title' => t('Value'),
      '#size' => 30,
      '#default_value' => $this->value,
    );
  }

  function options_form(&$form, &$form_state) {
    parent::options_form(&$form, &$form_state);
    $form['xpath'] = array(
      '#type' => 'textfield',
      '#title' => t('XPath query'),
      '#default_value' => $this->options['xpath'],
      '#weight' => -3,
    );
    $form['cast_as'] = array(
      '#type' => 'select',
      '#title' => t('Cast as'),
      '#default_value' => $this->options['cast_as'],
      '#options' => array(
        'BINARY' => 'Binary',
        'CHAR' => 'Char',
        'SIGNED' => 'Signed Integer',
        'UNSIGNED' => 'Unsigned Integer',
      ),
      '#weight' => -3,
    );
    $form['case'] = array(
      '#type' => 'checkbox',
      '#title' => t('Case sensitive'),
      '#default_value' => $this->options['case'],
      '#description' => t('Case sensitive filters may be faster. MySQL might ignore case sensitivity. Only applies to strings.'),
    );
  }

  function query() {
    $this->ensure_my_table();
    $field = "$this->table_alias.$this->real_field";
    $upper = $this->case_transform();

    $info = $this->operators();
    if (!empty($info[$this->operator]['method'])) {
      $this->{$info[$this->operator]['method']}($field, $upper, $this->options['cast_as']);
    }
  }

  function case_transform() {
    return empty($this->options['case']) ? '' : 'UPPER';
  }

  function op_equal($field, $upper, $cast_as) {
    $this->query->add_where($this->options['group'],
      "$upper(CAST(EXTRACTVALUE(%s, '%s') AS $cast_as)) $this->operator $upper(CAST('%s' AS $cast_as))",
      $field, $this->options['xpath'], $this->value
    );
  }

  function op_contains($field, $upper, $cast_as) {
    $this->query->add_where($this->options['group'],
      "$upper(CAST(EXTRACTVALUE(%s, '%s') AS $cast_as)) LIKE $upper(CONCAT('%%', CAST('%s' AS $cast_as), '%%'))",
      $field, $this->options['xpath'], $this->value
    );
  }

  function op_starts($field, $upper, $cast_as) {
    $this->query->add_where($this->options['group'],
      "$upper(CAST(EXTRACTVALUE(%s, '%s') AS $cast_as)) LIKE $upper(CONCAT(CAST('%s' AS $cast_as), '%%'))",
      $field, $this->options['xpath'], $this->value
    );
  }

  function op_ends($field, $upper, $cast_as) {
    $this->query->add_where($this->options['group'],
      "$upper(CAST(EXTRACTVALUE(%s, '%s') AS $cast_as)) LIKE $upper(CONCAT('%%', CAST('%s' AS $cast_as)))",
      $field, $this->options['xpath'], $this->value
    );
  }

  function op_regexp($field, $upper, $cast_as) {
    $binary = $upper != 'UPPER' ? '' : 'BINARY ';
    $this->query->add_where($this->options['group'],
      "EXTRACTVALUE(%s, '%s') $this->operator $binary'%s'",
      $field, $this->options['xpath'], $this->value
    );
  }
}

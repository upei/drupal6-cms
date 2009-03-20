<?php
//$Id: date_api.views.inc,v 1.1.4.33 2008/08/04 10:54:58 karens Exp $

/**
 * @file
 * Defines date-related Views data and plugins:
 * 
 * Date argument:
 *   A generic date argument that has an option to select one or more 
 *   Views date fields to filter on, automatically adds them to the view, 
 *   and then filters the view by the value of the selected field(s). 
 *   The flexible argument will accept and evaluate most ISO date
 *   and period formats, like 2009-05-01, 2008-W25, P1W. 
 * 
 * Date filter:
 *   A generic date filter that has an option to select a 
 *   Views date field to filter on, with a choice of a widget to use
 *   for the filter form and an option to set the default value to 
 *   a set date or something like 'now +90 days'. If the operator is 
 *   set to 'between' or 'not between' you can set a default value for
 *   both the from and to dates. 
 * 
 * Current date argument default
 *   Adds a default option to set the argument to the current date 
 *   when the argument is empty.
 * 
 * Date navigation attachment
 *   Navigation that can be attached to any display to create back/next 
 *   links by date, requires the date argument and uses the current
 *   date argument default to set a starting point for the view.
 */
//views_include_handlers();
/**
 * Implementation of hook_views_data()
 */
function date_api_views_data() {
  $data = array();
  
  // The flexible date argument.
  $data['node']['date_argument'] = array(
    'group' => t('Date'),
    'title' => t('Date'),
    'help' => t('Filter any Views date field by a date argument, using any common ISO date/period format (i.e. YYYY, YYYY-MM, YYYY-MM-DD, YYYY-W99, YYYY-MM-DD--P3M, P90D, etc).'),
    'argument' => array(
      'handler' => 'date_api_argument_handler',
      'empty name field' => t('Undated'),
    ),
  );  
  // The flexible date fliter.
  $data['node']['date_filter'] = array(
    'group' => t('Date'),
    'title' => t('Date'),
    'help' => t('Filter any Views date field.'),
    'filter' => array(
      'handler' => 'date_api_filter_handler',
      'empty name field' => t('Undated'),
    ),
  );  
  return $data;
}

/**
 * Implementation of hook_views_plugins
 */
function date_api_views_plugins() {
  $path = drupal_get_path('module', 'date_api');
  $base = array(
    'file' => 'theme.inc',
    'path' => "$path/theme",
  );
  return array(
    'module' => 'date_api', // This just tells our themes are elsewhere.
    'display' => array(
      // Display plugin for date navigation.
      'date_nav' => $base + array(
        'title' => t('Date browser'),
        'help' => t('Date back/next navigation to attach to other displays. Requires the Date argument.'),
        'handler' => 'date_plugin_display_attachment',
        'theme' => 'views_view',
        'use ajax' => TRUE,
        'admin' => t('Date browser'),
        'help topic' => 'display-date_navigation',
      ),
    ),
    'style' => array(
      // Style plugin for the navigation display.
      'date_nav' => $base + array(
        'title' => t('Date browser style'),
        'help' => t('Creates back/next navigation.'),
        'handler' => 'date_navigation_plugin_style',
        'theme' => 'date_navigation',
        'uses row plugin' => FALSE,
        'uses fields' => FALSE,
        'uses options' => TRUE,
        'type' => 'date_nav', 
        'even empty' => TRUE,
      ),
    ),
  );
}

/**
 * Date API argument handler.
 */
class date_api_argument_handler extends views_handler_argument_date {
  function construct() {
    parent::construct();
    include_once( drupal_get_path('module', 'date_api') .'/date_api_sql.inc');
    $this->date_handler = new date_sql_handler();
    $this->date_handler->construct();
  }

  /**
   * Get granularity and use it to create the formula and a format
   * for the results.
   */
  function init(&$view, $options) {
    parent::init($view, $options);
    
    // Identify the type of display we're using.
    $this->display_handler = $view->display_handler->definition['handler'];
    
    // Add a date handler to the display.
    $date_handler = $this->date_handler;
    $date_handler->granularity = $this->options['granularity'];
    $this->format = $date_handler->views_formats($date_handler->granularity, 'display');
    $this->sql_format = $date_handler->views_formats($date_handler->granularity, 'sql');
  }

  /**
   * Default value for the date_fields option.
   */
  function options(&$options) {
    parent::options($options);
    $options['date_fields'] = array();
    $options['date_method'] = 'OR';
    $options['granularity'] = 'month';
  }

  /**
   * Add a form element to select date_fields for this argument.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $options = $this->date_handler->date_parts();
    unset($options['second'], $options['minute']);
    $options += array('week' => t('Week'));
    $form['granularity'] = array(
      '#title' => t('Granularity'),
      '#type' => 'radios',
      '#options' => $options,
      '#default_value' => $this->options['granularity'],
      '#multiple' => TRUE,
      '#description' => t('Select the type of date value to be used in defaults, summaries, and navigation. For example, a granularity of \'month\' will set the default date to the current month, summarize by month in summary views, and link to the next and previous month when using date navigation.'),
    );

    $fields = date_api_fields();
    $options = array();
    foreach ($fields['name'] as $name => $field) {
      $options[$name] = $field['label'];
    }
    $form['date_fields'] = array(
      '#title' => t('Date field(s)'),
      '#type' => 'checkboxes',
      '#options' => $options,
      '#default_value' => $this->options['date_fields'],
      '#multiple' => TRUE,
      '#description' => t('Select one or more date fields to filter with this argument.'),
    );
    $form['date_method'] = array(
      '#title' => t('Method'),
      '#type' => 'radios',
      '#options' => array('OR' => t('OR'), 'AND' => t('AND')),
      '#default_value' => $this->options['date_method'],
      '#description' => t('Method of handling multiple date fields in the same query. Return items that have any matching date field (date = field_1 OR field_2), or only those with matches in all selected date fields (date = field_1 AND field_2).'),
      );
    
  }
    
  function options_validate($form, &$form_state) {
    $check_fields = array_filter($form_state['values']['options']['date_fields']);
    if (empty($check_fields)) {
      form_error($form['date_fields'], t('You must select at least one date field for this argument.'));
    }
  }
  
  function options_submit($form, &$form_state) {
    $form_state['values']['options']['date_fields'] = array_filter($form_state['values']['options']['date_fields']);
  }
  
  // Update the summary values to show selected granularity.
  function admin_summary() {
    if (!empty($this->options['date_fields'])) {
      return ' ('. implode(', ', $this->options['date_fields']) .')';
    }
    else {
      return parent::admin_summary();
    }
  }

  /**
   * Set the empty argument value to the current date, 
   * formatted appropriately for this argument.
   */
  function get_default_argument($raw = FALSE) {
    if (!$raw && $this->options['default_argument_type'] == 'date') {
      return date($this->format(), time());
    }
    else {
      return parent::get_default_argument($raw);
    }
  }
    
  function format() {
    if (!empty($this->options['granularity'])) {
      $date_handler = new date_sql_handler();
      return $date_handler->views_formats($this->options['granularity']);
    }
    else {
      return !empty($this->options[$this->option_name]) ? $this->options[$this->option_name] : 'Y-m';
    }
  }
    
  /**
   * Provide a link to the next level of the view from the summary.
   */
  function summary_name($data) {
    $format = $this->date_handler->views_formats($this->options['granularity'], 'display');
    $value = $data->{$this->name_alias};
    $range = $date_handler->arg_range($value);
    return date_format_date($range[0], 'custom', $format);
  }

  /**
   * Need to override the basic link since base_alias is now a formula.
   */
  function summary_link($data, $url) {
    $value = $data->{$this->name_alias};
    return url("$url/$value");
  }

  /**
   * Provide a link to the next level of the view from the argument.
   */
  function title() {
    $format = $this->date_handler->views_formats($this->options['granularity'], 'display');
    $range = $this->date_handler->arg_range($this->argument);
    return date_format_date($range[0], 'custom', $format);
  }

  /**
   * Create a summary query that matches the granularity.
   *
   * Needed or Views will do a groupby on the complete date instead
   * of only the part of the date actually used in the argument.
   */
  function summary_query() {
    $this->get_query_fields();
    
    // No way to do summaries on more than one field at a time.
    if (count($this->query_fields) > 1) {
      return;
    }
    
    $field = $this->query_fields[0]['field'];
    $date_handler = $this->query_fields[0]['date_handler'];
      
    // Get the SQL format for this granularity, like Y-m,
    // and use that as the grouping value.
    $format = $date_handler->views_formats($this->options['granularity'], 'sql');
    $this->formula = $date_handler->sql_format($format, $date_handler->sql_field($field['fullname']));
    
    $this->ensure_my_table();
    
    // Make sure this field is added to the query so we have all necessary tables.
    $this->query->add_field($field['table_name'], $field['field_name']);
      
    // Add the computed field.
    $this->base_alias = $this->name_alias = $this->query->add_field(NULL, $this->formula, $field['queryname']);
    $this->query->set_count_field(NULL, $this->formula, $field['queryname']);    

    return $this->summary_basics(FALSE);
  }

  function get_query_fields() {
    $fields = date_api_fields();
    $fields = $fields['name'];
    $min_date = isset($this->min_date) ? $this->min_date : NULL;
    $min_utc = isset($this->min_utc) ? $this->min_utc : NULL;
    $max_date = isset($this->max_date) ? $this->max_date : NULL;
    $max_utc = isset($this->max_utc) ? $this->max_utc : NULL;
    $this->query_fields = array();
    foreach ($this->options['date_fields'] as $delta => $name) {
      if (array_key_exists($name, $fields) && $field = $fields[$name]) {
        $date_handler = new date_sql_handler();
        $date_handler->construct($field['sql_type'], date_default_timezone_name());
        $date_handler->granularity = $this->options['granularity'];
        date_views_set_timezone($date_handler, $this, $field);
        $this->query_fields[] = array('field' => $field, 'date_handler' => $date_handler);
      }
    }
  }
 
  /**
   * Set up the query for this argument.
   *
   * The argument sent may be found at $this->argument.
   */
  function query() { 
    $block_identifier = isset($this->view->block_identifier) ? $this->view->block_identifier : 'mini';
    if (!empty($this->view->block) && isset($_GET[$block_identifier])) {
      $mini_args = explode('/', str_replace($this->view->get_path() .'/', '', $_GET[$block_identifier]));
      $this->view->args = $mini_args;
      $i = 0;
      foreach ($this->view->argument as $argument) {
        if ($argument->field == 'date_argument') {
          $this->argument = $this->view->args[$argument->position];
          break;
        }
        $i++;
      }
    }
    
    $parts = $this->date_handler->arg_parts($this->argument);
    foreach ($parts[0]['date'] as $key => $part) {
      // The last part evaluated is the one that will 'stick'
      // as the date type.
      $this->granularity = $key;
      $this->$key = $part;
    }
    $range = $this->date_handler->arg_range($this->argument);
    $min_date = $range[0];
    $max_date = $range[1];
    $this->min_date = $min_date;
    $this->max_date = $max_date;
    
    $this->get_query_fields();
    if (!empty($this->query_fields)) {
      // Use set_where_group() with the selected date_method 
      // of 'AND' or 'OR' to create the where clause.
      $this->query->set_where_group($this->options['date_method'], 'date');
      foreach ($this->query_fields as $query_field) {
        $field = $query_field['field'];
        $date_handler = $query_field['date_handler'];
      
        // Explicitly add this table using add_table so Views does not
        // remove it if it is a duplicate, since that will break the query.
        $this->query->add_table($field['table_name'], NULL, NULL, $field['table_name']);
        // Make sure the real field is added to the query.
        $this->query->add_field($field['table_name'], $field['field_name']);
        foreach ($field['related_fields'] as $related) {
          $bits = explode('.', $related);
          if ($bits[1] != $field['field_name']) {
            $this->query->add_field($field['table_name'], $bits[1]);
          }
        }
        $from = $date_handler->sql_where_date('DATE', $field['fullname'], '>=', date_format($min_date, DATE_FORMAT_DATETIME));
        $to   = $date_handler->sql_where_date('DATE', $field['fullname'], '<=', date_format($max_date, DATE_FORMAT_DATETIME));
        $sql = str_replace('***table***', $field['table_name'], "($from AND $to)");
        if ($sql) {
          $this->query->add_where('date', $sql);
        }
      }
    }
  }
}
  
/**
 * The plugin that handles date navigation attachments.
 * 
 * Creates a special attachment for this purpose only. 
 */
class date_plugin_display_attachment extends views_plugin_display_attachment {
  
  // Require the date_nav style. That style has a date_nav type
  // so it won't show up as a style option on any other display.
  function get_style_type() { return 'date_nav'; }
  
  // No options to set style, force it to the right value.
  function defaultable_sections($section = NULL) {
    if (in_array($section, array('row_options', 'row_plugin', 'items_per_page'))) {
      return FALSE;
    }
    return parent::defaultable_sections($section);
  }

  function options(&$display) {
    parent::options($display);
    $display->display_options['style_plugin'] = 'date_nav';
    $display->display_options['items_per_page'] = 0;
    $display->display_options['row_plugin'] = '';
    //$display->display_options['defaults']['style_plugin'] = FALSE;
    $display->display_options['defaults']['style_options'] = FALSE;
    $display->display_options['defaults']['items_per_page'] = FALSE;
    $display->display_options['defaults']['row_plugin'] = FALSE;
    $display->display_options['defaults']['row_options'] = FALSE;
  } 

}

/**
 * Style plugin to create date back/next navigation.
 * 
 * The style plugin passes some argument values to the theme, and
 * ensures that the date argument is present and that the default
 * value is set to the current date.
 */
class date_navigation_plugin_style extends views_plugin_style {
  
  /**
   * Style validation.
   */
  function validate() {
    $errors = parent::validate();
    
    $arguments = $this->display->handler->get_option('arguments');
    $count = 0;
    $found = FALSE;
    foreach ($arguments as $id => $argument) {
      if ($argument['field'] == 'date_argument') {
        if ($count > 0) {
          $errors[] = t('The @style cannot use more than one Date: Date argument.', array('@style' => $this->definition['title']));          
        }
        elseif ($argument['default_argument_type'] != 'date') {
          $errors[] = t('The @style requires the Date: Date argument be set to default to the current date.', array('@style' => $this->definition['title']));      
        }
        $count++;
        $found = TRUE;
      }
    }
    if (!$found) {
      $errors[] = t('The @style requires the Date: Date argument.', array('@style' => $this->definition['title']));      
    }
    return $errors;
  }
  
  function query() {
    include_once(drupal_get_path('module', 'date_api') .'/date_api_sql.inc');
        
    // Bring the argument information into the view so our theme can access it.
    $i = 0;    
    foreach ($this->view->argument as $id => $argument) {
      if ($id == 'date_argument') {
        $this->view->granularity = $argument->granularity;
        $this->view->date_arg = $argument->argument;
        $this->view->date_arg_pos = $i;
        $this->view->year = isset($argument->year) ? $argument->year : NULL;
        $this->view->month = isset($argument->month) ? $argument->month: NULL;
        $this->view->day = isset($argument->day) ? $argument->day : NULL;
        $this->view->week = isset($argument->week) ? $argument->week : NULL;
        $this->view->min_date = $argument->min_date;
        $this->view->max_date = $argument->max_date;
        $this->view->url = $this->view->get_url();
      }
      $i++;
    }
     
    // bring the node type into the query so we can use it in the theme
    $this->view->query->add_field('node', 'type');
    parent::query();
  }
  
  /**
   * Render the calendar navigation style.
   */
  function render() {
    return theme($this->theme_functions(), $this->view, $this->options, array());
  }
}

/**
 * A flexible, configurable date filter.
 *
 * This filter allows you to select a granularity of date parts to filter on,
 * such as year, month, day, etc.
 *
 * Each part can be set to blank to show all values; 'now' to filter for
 * the current value of that part, or a specific value.
 *
 * An adjustment field is provided that will adjust the selected filter
 * value by something like '+90 days' or '-1 month';
 */
class date_api_filter_handler extends views_handler_filter_numeric {
  var $date_handler = NULL;

  // Add a date handler to the filter.
  function construct() {
    parent::construct();
    include_once( drupal_get_path('module', 'date_api') .'/date_api_sql.inc');
    $this->date_handler = new date_sql_handler();
    $this->date_handler->construct();
    $this->date_handler->granularity = $this->options['granularity'];
  }

  function init(&$view, $options) {
    parent::init($view, $options);
    $handler = $this->date_handler;
    $handler->granularity = isset($options['granularity']) ? $options['granularity'] : 'day';
    $handler->adjustment_field = isset($options['adjustment_field']) ? $options['adjustment_field'] : 0;
  }

  // Set default values for the date filter.
  function options(&$options) {
    parent::options($options);
    $options['date_fields'] = array();
    $options['granularity'] = 'day';
    $options['form_type'] = 'date_select';
    $options['default_date'] = '';
    $options['default_to_date'] = '';
  }
  
  function option_definition() {
    $options = parent::option_definition();
    return $options;
  }

  /**
   * Set the granularity of the date parts to use in the filter.
    */
  function has_extra_options() { return TRUE; }

  /**
   * Date selection options.
   * 
   * TODO Only select widget is working right now.
   */
  function widget_options() {
    $options = array(
      'date_select' => t('Select'), 
      //'date_text' => t('Text'), 
      //'date_popup' => t('Popup'),
      );
    //if (!module_exists('date_popup')) {
    //  unset($options['date_popup']);
    //}  
    return $options;
  }
   
  function extra_options_form(&$form, &$form_state) {
    $form['form_type'] = array(
      '#type' => 'radios',
      '#title' => t('Date form type'),
      '#default_value' => $this->options['form_type'],
      '#options' => $this->widget_options(),
      '#description' => t('Choose the form element to use for date selection (more options will be available later).'),
      );
   
    $form['granularity'] = $this->date_handler->granularity_form($this->options['granularity']);
    $form['granularity']['#description'] = '<p>'. t('Select a granularity for the date filter. For instance, selecting \'day\' will create a filter where users can select the year, month, and day.') .'</p>';
    
    $fields = date_api_fields();
    $options = array();
    foreach ($fields['name'] as $name => $field) {
      $options[$name] = $field['label'];
    }
    $form['date_fields'] = array(
      '#title' => t('Date field(s)'),
      '#type' => 'checkboxes',
      '#options' => $options,
      '#default_value' => $this->options['date_fields'],
      '#multiple' => FALSE,
      '#description' => t('Select date field(s) to filter with this argument.'),
    );
  }

  function extra_options_validate($form, &$form_state) {
    $check_fields = array_filter($form_state['values']['options']['date_fields']);
    if (empty($check_fields)) {
      form_error($form['date_fields'], t('You must select at least one date field for this filter.'));
    }
  }
  
  function extra_options_submit($form, &$form_state) {
    $form_state['values']['options']['date_fields'] = array_filter($form_state['values']['options']['date_fields']);
  }
    
  /**
   * Add the selectors to the value form using the date handler.
   */
  function value_form(&$form, &$form_state) {
    // We use different values than the parent form, so we must
    // construct our own form element.
    $form['value'] = array();
    $form['value']['#tree'] = TRUE;
    
    // We have to make some choices when creating this as an exposed
    // filter form. For example, if the operator is locked and thus
    // not rendered, we can't render dependencies; instead we only
    // render the form items we need.
    $which = 'all';
    $source = '';
    if (!empty($form['operator'])) {
      $source = ($form['operator']['#type'] == 'radios') ? 'radio:options[operator]' : 'edit-options-operator';
    }

    if (!empty($form_state['exposed'])) {
      if (empty($this->options['expose']['use_operator']) || empty($this->options['expose']['operator'])) {
        // exposed and locked.
        $which = in_array($this->operator, $this->operator_values(2)) ? 'minmax' : 'value';
      }
      else {
        $source = 'edit-' . form_clean_id($this->options['expose']['operator']);
      }
    }

    $handler = $this->date_handler;
       
    if ($which == 'all' || $which == 'value') {
      $form['value'] += $this->date_parts_form($form_state, 'value', $source, $which, $this->operator_values(1));
    }

    if ($which == 'all' || $which == 'minmax') {
      $form['value'] += $this->date_parts_form($form_state, 'min', $source, $which, $this->operator_values(2));
      $form['value'] += $this->date_parts_form($form_state, 'max', $source, $which, $this->operator_values(2));
    }
    
    $form['value']['value']['#prefix'] = t('<div class="form-item"><label>Absolute value</label></div>');
    $form['value']['default_date'] = array(
      '#type' => 'textfield',
      '#title' => t('Date default'),
      '#default_value' => $this->options['default_date'],
      '#prefix' => t('<div class="form-item"><label>Relative value</label><p>Relative values will be used if no date is set above. Use \'now\' to default to the current date at runtime or add modifiers like \'now +1 day\'. The To date default value is used when the operator is set to \'between\' or \'not between\'. </p><p>If the filter is exposed, these values will be used to set the inital value of the exposed filter. Leave both date and default values blank to start with no value in the exposed filter. </p></div>'),
      );
    $form['value']['default_to_date'] = array(
      '#type' => 'textfield',
      '#title' => t('To date default'),
      '#default_value' => $this->options['default_to_date'],
      );

    // Test if this value is in the UI or exposed, only show these elements in the UI.
    // We'll save it as an option rather than a value to store it for use
    // in the exposed filter.
    if (!empty($form_state['exposed'])) {
      $form['value']['default_date']['#type'] = 'hidden';
      $form['value']['default_date']['#value'] = $form['value']['default_date']['#default_value'];
      $form['value']['default_to_date']['#type'] = 'hidden';
      $form['value']['default_to_date']['#value'] = $form['value']['default_to_date']['#default_value'];
      unset($form['value']['default_date']['#prefix']);
    }
    
    $form['value']['#theme'] = 'date_views_filter_form';  
  }

  /**
   * A form element to select date part values.
   *
   * @param string $prefix
   *   A prefix for the date values, 'value', 'min', or 'max'.
   * @param string $source
   *   The operator for this element.
   * @param string $which
   *   Which element to provide, 'all', 'value', or 'minmax'.
   * @param array $operator_values
   *   An array of the allowed operators for this element.
   * @param array $limit
   *   An array of date parts to limit this element to.
   *
   * @return
   *   The form date part element for this instance.
   */
  function date_parts_form($form_state, $prefix, $source, $which, $operator_values) {
    include_once(drupal_get_path('module', 'date_api') .'/date_api_elements.inc');
    switch($prefix) {
      case 'min':
        $name = t('From date');
        break;
      case 'max':
        $name = t('To date');
        break;
      default:
        $name = '';
        break;
    }
    $type = $this->options['form_type'];
    $format = $this->date_handler->views_formats($this->options['granularity'], 'sql');
    $granularity = array_keys($this->date_handler->date_parts($this->options['granularity']));
    
    // Don't set a default date in the UI, only in the exposed form.
    $default_date = '';
    if (!empty($form_state['exposed'])) {
      $default_date = $this->default_value($prefix);
    }
    $form[$prefix] = array(
      '#type' => $type,
      '#title' => $name,
      '#size' => 20,
      '#default_value' => !empty($this->value[$prefix]) ? $this->value[$prefix] : $default_date,
      '#date_format' => date_limit_format($format, $granularity),
      '#date_label_position' => 'within',
    );
    if ($which == 'all') {
      $dependency = array(
        '#process' => array($type .'_process', 'views_process_dependency'),
        '#dependency' => array($source => $operator_values),
      );
      $form[$prefix] += $dependency;
    }
    return $form;
  }

   function default_value($prefix, $options = NULL) {
    $default_date = '';
    if (empty($options)) {
      $options = $this->options;
    }
    $default_option = $prefix == 'max' ? $options['default_to_date'] : $options['default_date'];
    if (!empty($default_option)) {
      $date = date_now();
      if ($add = trim(str_replace('now', '', $default_option))) {
        date_modify($date, $add);
      }
      $default_date = date_format($date, DATE_FORMAT_DATETIME);
    }
    return $default_date;
  }
  
  /**
   * Value validation.
   * 
   * TODO add in more validation.
   * 
   * We are setting an extra option using a value form
   * because it makes more sense to set it there. 
   * That's not the normal method, so we have to manually
   * transfer the selected value back to the option.
   */
  function value_validate(&$form, &$form_state) {
    if (($form_state['values']['options']['operator'] == 'between' || $form_state['values']['options']['operator'] == 'not between') && 
    !empty($form_state['values']['options']['value']['default_date']) && empty($form_state['values']['options']['value']['default_to_date'])) {
      form_error($form['value']['default_to_date'], t('Please set a default value for the To date as well as the From date when using default values with the Between or Not between operators.'));
    }
    if (isset($form_state['values']['options']['value']['default_date'])) {
      $this->options['default_date'] = $form_state['values']['options']['value']['default_date'];
      $this->options['default_to_date'] = $form_state['values']['options']['value']['default_to_date'];
    }
    parent::value_validate($form, $form_state);
  }

  /**
   * Be sure that default values get set properly when there is no input.
   */
  function accept_exposed_input($input) {
    if (empty($this->options['exposed'])) {
      return TRUE;
    }
    if (!empty($this->options['expose']['use_operator']) && !empty($this->options['expose']['operator']) && isset($input[$this->options['expose']['operator']])) {
      $this->operator = $input[$this->options['expose']['operator']];
    }
    if (!empty($this->options['expose']['identifier'])) {
      $value = $input[$this->options['expose']['identifier']];
      if (!isset($_GET[$this->options['expose']['identifier']])) {
        $value['min'] = $this->default_value('min');
        $value['max'] = $this->default_value('max');
        $value['value'] = $this->default_value('value');
      }
      
      // Various ways to check for the absence of optional input.
      if (!empty($this->options['expose']['optional'])) {
        if ($value == 'All' || $value === array()) {
          return FALSE;
        }
        if (!empty($this->no_single) && $value === '') {
          return FALSE;
        }
      }

      if (isset($value)) {
        $this->value = $value;
      }
      else {
        return FALSE;
      }
    }
    return TRUE;
  }
  
  // Update the summary values to provide
  // meaningful information for each option.
  function admin_summary() {
    if (empty($this->options['date_fields'])) {
      return t('Missing date fields!');
    }
    $handler = $this->date_handler;
    $field = implode(', ', $this->options['date_fields']);
    $output = "$field ". check_plain($this->operator) . ' ';
    $parts = $handler->date_parts();
    
    $widget_options = $this->widget_options();
    // If the filter is exposed, display the granularity.
    if ($this->options['exposed']) {
      return t('(@field) <strong>Exposed</strong> @widget @format', array('@field' => $field, '@format' => $parts[$handler->granularity], '@widget' => $widget_options[$this->options['form_type']]));
    }
    // If not exposed, display the value.
    if (in_array($this->operator, $this->operator_values(2))) {
      $min = check_plain(!empty($this->options['default_date']) ? $this->options['default_date'] : $this->options['value']['mindate']);
      $max = check_plain(!empty($this->options['default_to_date']) ? $this->options['default_to_date'] : $this->options['value']['maxdate']);
      $output .= t('@min and @max', array('@min' => $min, '@max' => $max));
    }
    else {
      $output .= check_plain(!empty($this->options['default_date']) ? $this->options['default_date'] : $this->options['value']['valuedate']);
    }
    return $output;
  }
 
  function op_between($field) {
    $this->date_filter('min', $field, '>=');
    $this->date_filter('max', $field, '<=');
    return;
  }

  function op_simple($field) {
    $this->date_filter('value', $field, $this->operator);
    return;
  }

  function date_filter($prefix, $field, $operator) {
    // If no value is supplied from an exposed filter use the default value.
    if (empty($this->options['exposed']) && empty($this->value[$prefix])) {
      $default = $this->default_value($prefix);
      if (empty($default)) {
        return;
      }
      else {
        $this->value[$prefix] = $default;
      }
    }
    // If there is no value, do no filtering.
    if (empty($this->value[$prefix])) {
      return;
    }
    $date_handler = $this->date_handler;
    $granularity = $this->options['granularity'];
    //$selected = $date_handler->arg_parts($this->value[$prefix]);
    //$complete_date = $date_handler->complete_date($selected[0]['date']);
    $complete_date = $this->value[$prefix];
    $date = date_make_date($complete_date);
    $this->format = $date_handler->views_formats($granularity, 'sql');
    $value = date_format($date, $this->format);
    $range = $this->date_handler->arg_range($value);
    $min_date = $range[0];
    $max_date = $range[1];
    
    $this->min_date = $min_date;
    $this->max_date = $max_date;
    
    $this->get_query_fields();
    if (!empty($this->query_fields)) {
      // Use set_where_group() with the selected date_method 
      // of 'AND' or 'OR' to create the where clause.
      //$this->query->set_where_group($this->options['date_method'], 'date');
      foreach ((array) $this->query_fields as $query_field) {
        $field = $query_field['field'];
        $date_handler = $query_field['date_handler'];
        $parts = $date_handler->date_parts();
    
        // Explicitly add this table using add_table so Views does not
        // remove it if it is a duplicate, since that will break the query.
        $this->query->add_table($field['table_name'], NULL, NULL, $field['table_name']);
        // Make sure the real field is added to the query.
        $this->query->add_field($field['table_name'], $field['field_name']);
        foreach ($field['related_fields'] as $related) {
          $bits = explode('.', $related);
          if ($bits[1] != $field['field_name']) {
            $this->query->add_field($field['table_name'], $bits[1]);
          }
        }
        $value = $prefix == 'max' ? date_format($max_date, $this->format) : date_format($min_date, $this->format);
        $sql = $date_handler->sql_where_format($this->format, $field['fullname'], $operator, $value);
        $this->query->add_where($this->options['group'], $sql);
        continue;
      }
    }
  }
  
  function get_query_fields() {
    $fields = date_api_fields();
    $fields = $fields['name'];
    $min_date = isset($this->min_date) ? $this->min_date : NULL;
    $min_utc = isset($this->min_utc) ? $this->min_utc : NULL;
    $max_date = isset($this->max_date) ? $this->max_date : NULL;
    $max_utc = isset($this->max_utc) ? $this->max_utc : NULL;
    $this->query_fields = array();
    foreach ((array) $this->options['date_fields'] as $delta => $name) {
      if (array_key_exists($name, $fields) && $field = $fields[$name]) {
        $date_handler = new date_sql_handler();
        $date_handler->construct($field['sql_type'], date_default_timezone_name());
        $date_handler->granularity = $this->options['granularity'];
        date_views_set_timezone($date_handler, $this->view, $field);
        $this->query_fields[] = array('field' => $field, 'date_handler' => $date_handler);
      }
    }
  }
}

/**
 *  Identify all potential date/timestamp fields and cache the data.
 */
function date_api_fields($base = 'node', $reset = FALSE) {
  static $fields;
  if (empty($fields[$base]) || $reset) {
    $cid = 'date_api_fields_'. $base;
    if (!$reset && $cached = cache_get($cid, 'cache_views')) {
      $fields[$base] = $cached->data;
    }
    else {
      $fields[$base] = _date_api_fields($base);
    }
  }
  return $fields[$base];
}

/**
 *  Identify all potential date/timestamp fields.
 *
 *  @return
 *   array with fieldname, type, and table
 */
function _date_api_fields($base = 'node') {
  $cid = 'date_api_fields_'. $base;
  cache_clear_all($cid, 'cache_views');
  
  $all_fields = date_api_views_fetch_fields($base, 'field');
  $fields = array();
  foreach ((array) $all_fields as $name => $val) {
    $fromto = array();
    $tmp = explode('.', $name);
    $field_name = $tmp[1];
    $table_name = $tmp[0];
    $alias = str_replace('.', '_', $name);
      
    $handler = views_get_handler($table_name, $field_name, 'field');
    $type = '';
    
    // For cck fields, get the date type.
    if (isset($handler->content_field)) {
      if ($handler->content_field['type'] == 'date') {
        $type = 'cck_string';
      }
      elseif ($handler->content_field['type'] == 'datestamp') {
        $type = 'cck_timestamp';
      }
      elseif ($handler->content_field['type'] == 'datetime') {
        $type = 'cck_datetime';
      }
    }
    
    // This is a core timestamp field.
    elseif (strstr($field_name, 'timestamp') || strstr($field_name, 'updated') 
      || strstr($field_name, 'created') || strstr($field_name, 'changed')) {
      $type = 'timestamp';
    }
    

    // Don't do anything if this is not a date field we can handle.
    if (!empty($type)) {

      // Handling for simple timestamp fields
      $fromto = array($alias, $alias);
      $tz_handling = 'site';
      $related_fields = array();
      $timezone_field = '';
      $offset_field = '';
      $rrule_field = '';
      $granularity = array('year', 'month', 'day', 'hour', 'minute');
       
      // Handling for content field dates
      if (isset($handler->content_field['tz_handling'])) {
        $tz_handling = $handler->content_field['tz_handling'];
        $db_info = content_database_info($handler->content_field);
        if ($tz_handling == 'date') {
          $offset_field = $table_name .'.'. $db_info['columns']['offset']['column'];
        }
        $related_fields = array(
          $table_name .'.'. $field_name
          );
        if (isset($db_info['columns']['value2']['column'])) {
          $related_fields = array_merge($related_fields, array($table_name .'.'. $db_info['columns']['value2']['column']));
        }
        if (isset($db_info['columns']['timezone']['column'])) {
          $related_fields = array_merge($related_fields, array($table_name .'.'. $db_info['columns']['timezone']['column']));
          $timezone_field = $table_name .'.'. $db_info['columns']['timezone']['column'];
        }
        if (isset($db_info['columns']['rrule']['column'])) {
          $related_fields = array_merge($related_fields, array($table_name .'.'. $db_info['columns']['rrule']['column']));
          $rrule_field = $table_name .'.'. $db_info['columns']['rrule']['column'];
        }
      }

      // Handling for cck fromto dates
      if (isset($handler->content_field)) {
        switch ($handler->content_field['type']) {
          case 'date':
          case 'datetime':
          case 'datestamp':
            $db_info = content_database_info($handler->content_field);
            $fromto = array(
              $table_name .'_'. $db_info['columns']['value']['column'],
              $table_name .'_'. ($handler->content_field['todate'] ? $db_info['columns']['value2']['column'] : $db_info['columns']['value']['column']),
              );
            break;
        }
        $granularity = $handler->content_field['granularity'];
      }
      
      // CCK fields append a column name to the field, others do not
      // need a real field_name with no column name appended for cck date formatters
      switch ($type) {
        case 'cck_string':
          $sql_type = DATE_ISO;
          break;
        case 'cck_datetime':
          $sql_type = DATE_DATETIME;
          break;
        default:
          $sql_type = DATE_UNIX;
          break;
      }
      $fields['name'][$name] = array(
        'type' => $type,
        'sql_type' => $sql_type,
        'label' => $val['group'] .': '. $val['title'],
        'granularity' => $granularity,
        'fullname' => $name,
        'table_name' => $table_name,
        'field_name' => $field_name,
        'query_name' => $alias,
        'fromto' => $fromto,
        'tz_handling' => $tz_handling,
        'offset_field' => $offset_field,
        'timezone_field' => $timezone_field,
        'rrule_field' => $rrule_field,
        'related_fields' => $related_fields,
      );
      if (isset($handler->content_field)) {
        if (substr($field_name, -1) == '2') {
          $len = (strlen($field_name) - 7);
        }
        else {
          $len = (strlen($field_name) - 6);
        }
        $fields['name'][$name]['real_field_name'] = substr($field_name, 0, $len);
      }
      else {
        $fields['name'][$name]['real_field_name'] = $field_name;
      }
      $fields['alias'][$alias] = $fields['name'][$name];
    }
  }
  
  //cache_set($cid, $fields, 'cache_views');
  return $fields;
}

/**
 * Central function for setting up the right timezone values
 * in the SQL date handler.
 * 
 * The date handler will use this information to decide if the
 * database value needs a timezone conversion.
 * 
 * In Views, we will always be comparing to a local date value,
 * so the goal is to convert the database value to the right
 * value to compare to the local value.
 */
function date_views_set_timezone(&$date_handler, &$view, $field) {
  $tz_handling  = $field['tz_handling'];
  switch ($tz_handling) {
    case 'date' :
      $date_handler->db_timezone = 'UTC';
      $date_handler->local_timezone_field = $field['timezone_field'];
      $date_handler->local_offset_field = $field['offset_field'];
      break;
    case 'none':
      $date_handler->db_timezone = date_default_timezone_name();
      $date_handler->local_timezone = date_default_timezone_name();
      break;
    case 'utc':
      $date_handler->db_timezone = 'UTC';
      $date_handler->local_timezone = 'UTC';
      break;
    default :
      $date_handler->db_timezone = 'UTC';
      $date_handler->local_timezone = date_default_timezone_name();
      break;
  }
}
<?php
class views_plugin_style_ajax extends views_plugin_style {

  function options(&$options) {
    $options['include_nodes'] = array('default' => TRUE);
  }

  function options_form(&$form, &$form_state) {
    $form['include_nodes'] = array(
      '#type' => 'checkbox',
      '#default_value' => $this->options['include_nodes'],
      '#title' => t('Include raw node output'),
    );
  }
  function render() {
    if (empty($this->row_plugin)) {
      vpr('views_plugin_style_default: Missing row plugin');
      return;
    }

    // grouping
    $sets = $this->render_grouping($this->view->result, $this->options['grouping']);

    // render each group separately
    $output = array();
    foreach ($sets as $title => $records) {
      $rows = array();
      $nodes = array();
      foreach ($records as $label => $row) {
        $rendered_row = $this->row_plugin->render($row);
        $fields = array();
        $nodes[] = $row;
        foreach ($rendered_row as $field) {
          $fields[$field->label] = $field->content;
        }
        $rows[] = $fields;
      }
      if (empty($this->options['include_nodes'])) {
        $output[] = array(
          'title' => $title,
          'rows' => $rows,
        );

      }
      else {
        $output[] = array(
          'title' => $title,
          'rows' => $rows,
          'nodes' => $nodes,
        );
      }
    }
    return $output;
  }

}


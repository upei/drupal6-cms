<?php
class views_plugin_style_ajax extends views_plugin_style {
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
      foreach ($records as $label => $row) {
        $rendered_row = $this->row_plugin->render($row);
        $fields = array();
        foreach ($rendered_row as $field) {
          $fields[$field->label] = $field->content;
        }
        $rows[] = $fields;
      }
      $output[] = array(
        'title' => $title,
        'rows' => $rows,
      );
    }
    return $output;
  }

}


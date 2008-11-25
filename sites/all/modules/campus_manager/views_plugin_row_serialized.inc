<?php

class views_plugin_row_serialized extends views_plugin_row {

}


function template_preprocess_views_view_row_serialized(&$vars) {
  $view = $vars['view'];
  print('preprocess');
  // Loop through the fields for this view.
  foreach ($view->field as $id => $field) {
    if (!empty($field) && is_object($field)) {
      $object = new stdClass();
      $object->content = $field->theme($vars['row']);
      if (isset($field->field_alias) && isset($vars['row']->{$field->field_alias})) {
        $object->raw = $vars['row']->{$field->field_alias};
      }
      else {
        $object->raw = NULL; // make sure it exists to reduce NOTICE
      }
      if (!empty($vars['options']['separator']) && $object->content) {
        $object->separator = filter_xss($vars['options']['separator']);
      }

      $object->handler = $field;
      $object->class = views_css_safe($id);
      $object->label = check_plain($field->label());
      $vars['fields'][$id] = $object;
    }
  }
}
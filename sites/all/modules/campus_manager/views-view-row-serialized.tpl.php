<?php

$fields = array();
foreach ($view->field as $id => $field) {
  if (!empty($field) && is_object($field)) {
    $object = new stdClass();
    $object->content = $field->theme($row);
    if (isset($field->field_alias) && isset($row->{$field->field_alias})) {
      $object->raw = $row->{$field->field_alias};
    }
    else {
      $object->raw = NULL; // make sure it exists to reduce NOTICE
    }
    if (!empty($options['separator']) && $object->content) {
      $object->separator = filter_xss($options['separator']);
    }

    $object->handler = $field;
    $object->class = views_css_safe($id);
    $object->label = check_plain($field->label());
    $fields[$id] = $object;
  }
}

$final = new stdClass();
foreach($fields as $field_label => $object) {
  $label = $field_label;
  $final->{$object->label} = $object->content;
}
print serialize($final) . PHP_EOL;

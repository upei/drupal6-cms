<?php

class views_plugin_row_serialized extends views_plugin_row {
	function render($row) {
		$fields = $this->view->field;
		$result = array();
		// loop through the fields for this view
		foreach ($fields as $id => $field) {
			if (!empty($field) && is_object($field)) {
				$object = new stdClass();
				$object->content = $field->theme($row);
				if (isset($field->field_alias) && isset($row->{$field->field_alias})) {
					$object->raw = $row->{$field->field_alias};
				}
				else {
					$object->raw = NULL; // make sure it exists to reduce NOTICE
				}
				
				$object->handler = $field;
				$object->class = views_css_safe($id);
				$object->label = check_plain($field->label());
				$result[$id] = $object;
			}
		}
		return $result;
	}
}


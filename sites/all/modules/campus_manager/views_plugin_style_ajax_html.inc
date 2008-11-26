<?php

require_once('views_plugin_style_ajax.inc');
class views_plugin_style_ajax_html extends views_plugin_style_ajax {
	function render() {
		$parsed = parent::render();
		$output = '';
		foreach ($parsed as $group) {
			$title = $group['title'];
			$rows = $group['rows'];
			$output .= theme($this->theme_functions(), $this->view, $this->options, $rows, $title);
		}
		drupal_set_header('Content-type: text/html; charset=utf-8');
		print $output;
		exit;
	}
}


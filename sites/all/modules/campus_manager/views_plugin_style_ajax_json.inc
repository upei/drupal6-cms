<?php

require_once('views_plugin_style_ajax.inc');

class views_plugin_style_ajax_json extends views_plugin_style_ajax {
	function render() {
		$output = parent::render();
		drupal_set_header('Content-type: text/javascript; charset=utf-8');
		print drupal_to_js($output);
		exit;
	}
}


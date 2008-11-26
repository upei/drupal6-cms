<?php

require_once('views_plugin_style_ajax.inc');
class views_plugin_style_ajax_html extends views_plugin_style_ajax {
	
	function options(&$options) {
		$options['template'] = '';
	}

	function options_form(&$form, &$form_state) {
		$form['template'] = array(
			'#type' => 'textarea',
			'#title' => t('PHP Code Template'),
			'#rows' => 20,
			'#cols' => 80,
			'#default_value' => $this->options['template'],
		);
	}

	function render() {
		$__parsed = parent::render();
		$__output = '';
		foreach ($__parsed as $group) {
			$title = $group['title'];
			$rows = $group['rows'];
			$view =& $this->view;
			$options =& $this->options;
			if (!empty($this->options['template'])) {
				ob_start();
				print eval('?>' . $this->options['template']);
				$__output .= ob_get_contents();
				ob_end_clean();
			}
			else {
				$__output .= theme($this->theme_functions(), $this->view, $this->options, $rows, $title);
			}
		}
		drupal_set_header('Content-type: text/html; charset=utf-8');
		print $__output;
		exit;
	}
}


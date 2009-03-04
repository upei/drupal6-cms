<?php

require_once('views_plugin_style_ajax.inc');
class views_plugin_style_ajax_download extends views_plugin_style_ajax {
  
  function options(&$options) {
    $options['content_type'] = 'application/octet-stream';
    $options['field'] = '';
    $options['method'] = 'direct';
  }

  function options_form(&$form, &$form_state) {
    $form['content_type'] = array(
      '#id' => 'views_plugin_style_ajax_download_content_type',
      '#type' => 'textfield',
      '#title' => t('Content type of the download file'),
      '#default_value' => $this->options['content_type'],
      '#required' => true,
    );
    $form['field'] = array(
      '#id' => 'views_plugin_style_ajax_download_field',
      '#type' => 'textfield',
      '#title' => t('The label of the file field to download'),
      '#description' => t('Please choose a FileField and enter its field label'),
      '#required' => true,
      '#default_value' => $this->options['field']
      );
    $form['method'] = array(
      '#id' => 'views_plugin_style_ajax_download_method',
      '#type' => 'select',
      '#title' => 'Download method',
      '#description' => 'Choose the download method. Change the field\'s display format to Raw URL when using Direct downlload. Change the display format to Raw path when using Send through drupal and X-Sendfile header.',
      '#default_value' => $this->options['method'],
      '#options' => array(
        'direct' => t('Direct download'),
        'drupal' => t('Send through drupal'),
        'sendfile' => t('X-Sendfile header'),
        ),
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
    }
    $row = $rows[0];
    
    drupal_set_header('Content-type: ' . $options['content_type']);
    switch($options['method']) {
      case 'direct':
        drupal_goto($row[$options['field']]);
        break;
      case 'drupal':
        drupal_set_header('Content-disposition: attachment; filename="' . str_replace('"', '\"', basename($row[$options['field']])) . '"');
        $__output = file_get_contents($row[$options['field']]);
        print $__output;
        break;
      case 'sendfile':
        drupal_set_header('X-Sendfile: '. realpath($row[$options['field']]));
        break;
    }

    exit;
  }
}


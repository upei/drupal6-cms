<?php
// $Id: image_import.admin.inc,v 1.1 2008/06/13 22:01:09 drewish Exp $

function image_import_form() {
  $form = array();

  $dirpath = variable_get('image_import_path', '');
  if (!file_check_directory($dirpath)) {
    drupal_set_message(t("You need to configure the import directory on the image import module's <a href='!admin-settings-image_import'>settings page</a>.", array('!admin-settings-image_import' => url('admin/settings/image_import'))), 'error');
    return $form;
  }

  $files = file_scan_directory($dirpath, '.*');
  ksort($files);

  if ($files) {
    if (module_exists('taxonomy')) {
      // here's a little hack to get the taxonomy controls onto our form
      $form['type'] = array('#type' => 'value', '#value' => 'image');
      $form['#node'] = new stdClass();
      $form['#node']->type = 'image';
      taxonomy_form_alter($form, array(), 'image_node_form');
      unset($form['type']);
      unset($form['#node']);
    }

    // Put the image files into an array for the checkboxes and gather
    // additional information like dimensions and filesizes. Make sure that
    // there's no 0th element, because a checkbox with a zero value is seen as
    // unchecked and won't be imported.
    $fields = array('filesize', 'dimensions', 'title', 'body');
    foreach ($fields as $field) {
      $form['files'][$field][0] = NULL;
    }
    $filelist = array(0 => NULL);

    foreach ($files as $file) {
      $info = image_get_info($file->filename);
      if ($info && isset($info['extension'])) {
        $filelist[] = substr($file->filename, strlen($dirpath) + 1);
        $form['files']['filesize'][] = array(
          '#type' => 'item',
          '#value' => format_size(filesize($file->filename)),
        );
        $form['files']['dimensions'][] = array(
          '#type' => 'item',
          '#value' => $info['width'] .'x'. $info['height'],
        );
        $form['files']['title'][] = array(
          '#type' => 'textfield',
          '#size' => 20,
          '#default_value' => basename($file->name),
        );
        $form['files']['body'][] = array(
          '#type' => 'textfield',
          '#size' => 20,
        );
      }
    }
    // Remove our 0 elements.
    unset($filelist[0]);
    foreach ($fields as $field) {
      $form['files'][$field][0] = NULL;
    }

    // Put the titles into an array.
    $form['files']['title']['#tree'] = TRUE;
    $form['files']['body']['#tree'] = TRUE;

    // Store a copy of the list into a form value so we can compare it to what
    // they submit and not have to worry about files being added or removed from
    // the filesystem.
    $form['file_list'] = array(
      '#type' => 'value',
      '#value' => $filelist,
    );
    $form['import_file'] = array(
      '#type' => 'checkboxes',
      '#options' => $filelist,
    );

    $form['buttons']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Import'),
    );
  }
  else {
    $form['import_file'] = array(
      '#type' => 'item',
      '#value' => t('No files were found'),
    );
  }

  return $form;
}


function theme_image_import_form($form) {
  $output = '';
  if (isset($form['import_file']) && $form['import_file']['#type'] == 'checkboxes') {
    $header = array(theme('table_select_header_cell'), t('Name'), t('Size'), t('Dimensions'), t('Title'), t('Body'));
    $rows = array();
    foreach (element_children($form['import_file']) as $key) {
      $filename = $form['import_file'][$key]['#title'];
      unset($form['import_file'][$key]['#title']);
      $rows[] = array(
        drupal_render($form['import_file'][$key]),
        $filename,
        drupal_render($form['files']['filesize'][$key]),
        drupal_render($form['files']['dimensions'][$key]),
        drupal_render($form['files']['title'][$key]),
        drupal_render($form['files']['body'][$key]),
      );
    }
    $output .= theme('table', $header, $rows);
  }
  return $output . drupal_render($form);
}

function image_import_form_submit($form, &$form_state) {
  $op = isset($form_state['values']['op']) ? $form_state['values']['op'] : '';
  if ($op == t('Import')) {
    $dirpath = variable_get('image_import_path', '');
    if (file_check_directory($dirpath)) {
      $nodes = array();
      $files = array();
      foreach (array_filter($form_state['values']['import_file']) as $index) {
        // try to avoid php's script timeout with a bunch of large files or
        // a slow machine
        if (!ini_get('safe_mode')) {
          set_time_limit(0);
        }
        $origname = $form_state['values']['file_list'][$index];
        $filename = file_check_location($dirpath .'/'. $origname, $dirpath);
        if ($filename) {
          $node = image_create_node_from(
            $filename,
            $form_state['values']['title'][$index],
            $form_state['values']['body'][$index],
            $form_state['values']['taxonomy']
          );

          if ($node) {
            $nodes[] = t('%filename as <a href="!node-link">@node-title</a> <a href="!edit-link">[edit]</a>', array(
              '%filename' => $origname,
              '!node-link' => url('node/'. $node->nid),
              '@node-title' => $node->title,
              '!edit-link' => url('node/'. $node->nid .'/edit'),
            ));
          }
          else {
            drupal_set_message(t('Error importing %filename.', array('%filename' => $filename)));
          }
        }
      }

      // report back on our progress
      if (!empty($nodes)) {
        drupal_set_message(t('Successfully imported: ') . theme('item_list', $nodes));
      }
      else {
        drupal_set_message(t('No image files were imported.'));
      }
    }
  }
}

function image_import_admin_settings() {
  $form['image_import_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Import path'),
    '#default_value' => variable_get('image_import_path', file_directory_path() .'/images/import'),
    '#after_build' => array('_image_import_settings_check_directory'),
    '#description' => t("The directory to import image nodes from. Drupal will need to have write access to this directory so we can move the file.") .'<br />'
      . t("<strong>Note:</strong> a path begining with a <kbd>/</kbd> indicates the path is relative to the server's root, not the website's root. One starting without a <kbd>/</kbd> specifies a path relative to Drupal's root. For example: <kbd>/tmp/image</kbd> would be the temp directory off the root while <kbd>tmp/image</kbd> would be inside Drupal's directory."),
    '#required' => TRUE,
  );

  return system_settings_form($form);
}

/**
 * Checks the existence of the directory specified in $form_element.
 *
 * @param $form_element
 *   The form element containing the name of the directory to check.
 * @see system_check_directory()
 */
function _image_import_settings_check_directory($form_element) {
  $import_dir = $form_element['#value'];
  file_check_directory($import_dir, 0, $form_element['#parents'][0]);
  $image_dir = file_create_path(variable_get('image_default_path', 'images'));
  if (realpath($import_dir) == realpath($image_dir)) {
    form_set_error($form_element['#parents'][0], t("You can't import from the image module's directory. The import deletes the original files so you would just be asking for trouble."));
  }
  return $form_element;
}

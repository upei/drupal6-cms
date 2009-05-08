<?php

// $Id: imagefield_crop_widget.inc,v 1.1.2.7 2009/03/12 11:32:12 yhager Exp $

// load imagefield widget, so we can extend it, and not fully replace it
module_load_include('inc','imagefield', 'imagefield_widget');


function imagefield_crop_widget_settings_form($widget) {
  $form = module_invoke('imagefield', 'widget_settings_form', $widget);
  $form['collapsible'] = array(
    '#type' => 'radios',
    '#title' => t('Collapsible behavior'),
    '#options' => array(
      1 => t('None.'),
      2 => t('Collapsible, expanded by default.'),
      3 => t('Collapsible, collapsed by default.'),
    ),
    '#default_value' => isset($widget['collapsible']) ? $widget['collapsible'] : 2,
  );
  $form['resolution'] = array(
    '#type' => 'textfield', 
    '#title' => t('The resolution to crop the image onto'), 
    '#default_value' => isset($widget['resolution']) ? $widget['resolution'] : '200x150',
    '#size' => 15, 
    '#maxlength' => 10, 
    '#description' => 
    t('The output resolution of the cropped image, expressed as WIDTHxHEIGHT (e.g. 640x480). Set to 0 not to rescale after cropping. Note: output resolution must be defined in order to present a dynamic preview.'),
    '#element_validate' => array('_imagefield_crop_widget_settings_resolution_validate'),
  );
  $form['enforce_ratio'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enforce box crop box ratio'),
    '#default_value' => isset($widget['enforce_ratio']) ? $widget['enforce_ratio'] : 1,
    '#description' => t('Check this to force the ratio of the output on the crop box. NOTE: If you leave this unchecked but enforce an output resolution, the final image might be distorted'),
    '#element_validate' => array('_imagefield_crop_widget_settings_enforce_ratio_validate'),
  );

  $form['croparea'] = array(
    '#type' => 'textfield',
    '#title' => t('The resolution of the cropping area'),
    '#default_value' => isset($widget['croparea']) ? $widget['croparea'] : '500x500',
    '#size' => 15,
    '#maxlength' => 10,
    '#description' => t('The resolution of the area used for the cropping of the image. Image will displayed at this resolution for cropping. Use WIDTHxHEIGHT format, zero values are permitted, e.g. 500x0 will limit crop box to 500 pixels width.'),
    '#element_validate' => array('_imagefield_crop_widget_settings_croparea_validate'),
  );
  
  return $form;
}

function _imagefield_crop_widget_settings_resolution_validate($element, &$form_state) {
  list($rw, $rh) = explode('x', $form_state['values']['resolution']);
  if ($form_state['values']['enforce_ratio'] &&
      (!is_numeric($rw) || intval($rw) != $rw || $rw <= 0 ||
       !is_numeric($rh) || intval($rh) != $rh || $rh <= 0)) {
    form_error($element, t('Target resolution must be defined as WIDTHxHEIGHT if resolution is to be enforced'));
  }
}

function _imagefield_crop_widget_settings_enforce_ratio_validate($element, &$form_state) {
  if ($form_state['values']['resolution'] && !$form_state['values']['enforce_ratio']) {
    drupal_set_message('Output resolution is defined, but not enforced. Final images might be distroted');
  }
}

function _imagefield_crop_widget_settings_croparea_validate($element,&$form_state) {
  if ($form_state['values']['croparea']) {
    list($cw, $ch) = explode('x', $form_state['values']['croparea']);
    if (!is_numeric($cw) || intval($cw) != $cw || $cw < 0 ||
        !is_numeric($ch) || intval($ch) != $ch || $ch < 0) {
      form_error($element, t('Crop area resolution must be defined as WIDTHxHEIGHT'));
    }
  }
}

function imagefield_crop_widget_settings_validate($widget) {
  module_invoke('imagefield', 'widget_settings_validate', $widget);
}

function imagefield_crop_widget_settings_save($widget) {
  $settings = array('collapsible', 'resolution', 'enforce_ratio', 'croparea');
  return array_merge($settings, module_invoke('imagefield', 'widget_settings_save', $widget));
}

/**
 * FormAPI theme function. Theme the output of an image field.
 */
function theme_imagefield_crop_widget(&$element) {
  return theme('form_element', $element, $element['#children']);
}

function imagefield_crop_widget_process($element, $edit, &$form_state, $form) {
  static $added_js;

  $module_path = drupal_get_path('module', 'imagefield_crop');
  drupal_add_js($module_path . '/Jcrop/js/jquery.Jcrop.js');
  // We must define Drupal.behaviors for ahah to work, even if there is no file
  drupal_add_js($module_path . '/imagefield_crop.js');
  drupal_add_css($module_path . '/Jcrop/css/jquery.Jcrop.css');

  $file = $element['#value'];

  $field = content_fields($element['#field_name'], $element['#type_name']);

  // check remove buttons...
  $remove_name = $element['#field_name'] .'_'. $element['#delta'] .'_remove_btn';
  if (isset($form_state['clicked_button']) && $form_state['clicked_button']['#name'] == $remove_name) {
    return $element;
  }

  if ($field['widget']['resolution']) {
    list($w, $h) = explode('x', $field['widget']['resolution']);

    // ratio is zero when not enforced
    $ratio = $field['widget']['enforce_ratio'] * $w/$h;
  }
  else {
    // no output resolution requested
    $ratio = 0;
  }

  if ($field['widget']['croparea']) {
    list($bwidth, $bheight) = explode('x', $field['widget']['croparea']);
  }
  else {
    $bwidth = $bheight = 0;
  }
  $element['#collapsible'] = ($field['widget']['collapsible'] != 1);
  $element['#collapsed'] = ($field['widget']['collapsible'] == 3);

  $defaults = array(
    'x'       => 0,
    'y'       => 0,
    'width'   => $w ? $w : 50,
    'height'  => $h ? $h : 50,
    'changed' => 0,
  );

  if (!$added_js) {
    // Add settings only once (for ahah).
    $settings = array(
      'ratio' => $ratio,
      'box_width' => (integer)$bwidth,
      'box_height' => (integer)$bheight,
    );
    drupal_add_js(array('imagefield_crop' => $settings), 'setting');
    $added_js = TRUE;
  }

  if (!empty($file) && 
      is_file($file['filepath']) &&
      (list($width, $height, $type, $image_attributes) = @getimagesize($file['filepath']))) {

    if ($field['widget']['enforce_ratio']) {
      $image_ratio = $width/$height;
      if ($ratio > $image_ratio) {
        $height = $width/$ratio;
      }
      else {
        $width = $height*$ratio;
      }
      // if the enforced ratio is different, force crop
      $defaults['changed'] = ($ratio != $image_ratio);
      
    }
    $defaults['width'] = $width;
    $defaults['height'] = $height;
  }
  
  $crop_display = $file;
  $crop_display['filepath'] = imagefield_crop_file_admin_crop_display_path($file);
  $element['data']['cropbox'] = array(
    '#type' => 'markup',
    '#value' => theme('imagefield_crop_cropbox', $crop_display, $crop_display['alt'], $crop_display['title'], NULL, FALSE),
  );
  
  $element['data']['crop'] = array(
    '#weight' => -10,
  );
  
  foreach ($defaults as $name => $default) {
    $element['data']['crop'][$name] = array(
      '#type' => 'hidden',
      '#title' => $name,
      '#attributes' => array('class' => 'edit-image-crop-'. $name),
      '#value' => $file['data']['crop'][$name] ? $file['data']['crop'][$name] : $default,
    );
  }
  
  // show dynamic crop preview
  $element['preview'] = array(
      '#type' => 'markup',
      '#value' => theme('imagefield_crop_dynamic_preview', $crop_display, $field['widget']['resolution']),
    );

  return $element;
}

function imagefield_crop_widget_value($element, $edit = FALSE) {
  if ($edit) {
    $file = field_file_load($edit['fid']);
    $field = content_fields($element['#field_name'], $element['#type_name']);
    
    $crop = $edit['data']['crop'];
    if ($field['widget']['resolution']) {
      list($scale['width'], $scale['height']) = explode('x', $field['widget']['resolution']);
    }
    if ($crop['changed']) {
      // save crop time, for preview
      variable_set('imagefield_crop_query_string', REQUEST_TIME);
      _imagefield_crop_resize(imagefield_crop_file_admin_original_path($file),
                              $crop,
                              $scale,
                              $file['filepath']);
    }
  }

  return module_invoke('filefield', 'widget_value', $element, $edit);
}

function imagefield_crop_widget_validate($element) {
  // Check if crop values are not empty
}


function theme_imagefield_crop_cropbox($file = NULL, $alt = '', $title = '', $attributes = NULL, $getsize = TRUE) {
  // REFACTOR: consider multiple images
  $attributes = array_merge((array)$attributes + array('id' => 'cropbox'));
  $output = theme('imagefield_image', $file, $alt, $title, $attributes, $getsize);
  $element = array(
    '#type' => 'element',
    '#title' => t('Crop area'),
  );
  return theme('form_element', $element, $output);
}


function theme_imagefield_crop_dynamic_preview($file, $resolution) {
  $file = (array)$file;
  if (!is_file($file['filepath'])) {
    return '<!-- file not found: '. $file['filepath'] .' -->';
  }
  list($width, $height) = explode('x', $resolution);
  
  $image_attributes = array();
  if (list($orig_width, $orig_height, $type, $image_attributes) = @getimagesize($file['filepath'])) {
    $alt = $file['alt'] ? $alt : 'jcrop preview';
    $title = $file['title'] ? $title : '';
    $url = file_create_url($file['filepath']);
    $settings = array(
      'orig_width' => $orig_width,
      'orig_height' => $orig_height,
      'width' => (integer)$width,
      'height' => (integer)$height,
    );
    // REFACTOR: Support multiple fields (i.e. add element delta to setting array)
    $output = '';
    $output .= '<script type="text/javascript">Drupal.settings.imagefield_crop.preview = '. drupal_to_js($settings) .'</script>';
    $output .= '<div class="jcrop-preview-wrapper" style="width:'. $width .'px;height:'. $height .'px;overflow:hidden;"><img src="'. check_url($url) .'" alt="'.
      check_plain($alt) .'" title="'. check_plain($title) .'" class="jcrop-preview" /></div>';
    return $output;
  }
  return '<!-- could not get imagesize, possibly corrupt or non image. '. $file['filepath'] .' -->';

  
}

function _imagefield_crop_resize($src, $crop = NULL, $scale = NULL, $dst = '') {
  $image = module_invoke('imageapi', 'image_open', $src);

  if ($image) {
    if ($crop) {
      module_invoke('imageapi', 'image_crop', $image, $crop['x'], $crop['y'], $crop['width'], $crop['height']);
    }

    if ($scale) {
      module_invoke('imageapi', 'image_scale', $image, $scale['width'], $scale['height']);
    }

    $result = module_invoke('imageapi', 'image_close', $image, $dst);
  }

  return $result;
}
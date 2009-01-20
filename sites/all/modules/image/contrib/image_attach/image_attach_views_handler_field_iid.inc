<?php


/**
 * Render an Image Attach field with options to control the size of the image
 * and the style of the link.
 */
class image_attach_views_handler_field_iid extends views_handler_field {
  function option_definition() {
    $options = parent::option_definition();

    $options['size'] = array('default' => IMAGE_THUMBNAIL);
    $options['as_link'] = array('default' => 'none');

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $sizes = image_get_sizes();
    $options = array();
    foreach($sizes as $name => $data) {
      $options[$name] = $data['label'] . '('. $data['width'] . 'x' . $data['height'] . ')';
    }
    $form['size'] = array(
      '#type' => 'select',
      '#title' => t('Image size'),
      '#options' => $options,
      '#default_value' => $this->options['size'],
    );

    $form['as_link'] = array(
      '#type' => 'select',
      '#title' => t('Link'),
      '#options' => array('none' => t('No link'), 'node' => t('Node'), 'image' => t('Image node')),
      '#default_value' => $this->options['as_link'],
    );
  }

  function render($values) {
    $image_node = node_load($values->image_attach_iid);

    if (!$image_node && node_access('view', $image_node)) {
      return '';
    }

    switch($this->options['as_link']) {
      case 'node':
        return l(image_display($image_node, $this->options['size']), 'node/' . $values->nid, array('html' => true));
      case 'image':
        return l(image_display($image_node, $this->options['size']), 'node/' . $image_node->nid, array('html' => true));
      default:
        return image_display($image_node, $this->options['size']);
    }
  }
}

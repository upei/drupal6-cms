<?php
// $Id: image_views_handler_field_image.inc,v 1.1 2009/01/13 10:10:41 drewish Exp $

/**
 * @file
 * Views handler for Image field.
 */

/**
 * Field handler to provide an image tag.
 */
class image_views_handler_field_image extends views_handler_field {
  function init(&$view, $options) {
    parent::init($view, $options);

    // Fields that are needed to build the image node manually.
    // @see image_views_handler_field_image::build_image_display_node()
    $this->additional_fields = array(
      'image_size' => array(
        'table' => 'image',
        'field' => 'image_size',
      ),
      'image_nid' => array(
        'table' => 'image',
        'field' => 'nid',
      ),
      'image_title' => array(
        'table' => 'node',
        'field' => 'title',
      ),
      'image_base_nid' => array(
        'table' => 'node',
        'field' => 'nid',
      ),
      'image_filepath' => array(
        'table' => 'files',
        'field' => 'filepath',
      ),
    );
  }

  /**
   * Defines default values for options.
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['link_to_node'] = array('default' => FALSE);
    $options['which_node'] = array('default' => 'image_node');
    return $options;
  }

  /**
   * Extends the field's basic options with more image specific
   * options.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['link_to_node'] = array(
      '#title' => t('Link the image to ...'),
      '#type' => 'checkbox',
      '#default_value' => $this->options['link_to_node'],
    );

    $form['which_node'] = array(
      '#title' => t('Which node to link to'),
      '#type' => 'radios',
      '#options' => array('image_node' => t('Image node'), 'base_node' => t('Base node')),
      '#default_value' => $this->options['which_node'],
      '#description' => t('<em>Image node</em> links to the node of the image itself. <em>Base node</em> links to the node from which this image is being referenced.'),
      '#process' => array('expand_radios', 'views_process_dependency'),
      '#dependency' => array('edit-options-link-to-node' => array(TRUE)),
      // This is needed for dependency to work with radios/checkboxes
      // as the dependency processing loses the actual radios after
      // expansion, so we help it out.
      // See "Special considerations" in views module's js/dependent.js
      '#prefix' => '<div><div id="edit-options-which-node">',
      '#suffix' => '</div></div>',
    );
  }

  /**
   * Make sure the image files relationship exists.
   *
   * @return
   *   Empty array if the handler is valid; an array of error strings if it is not.
   */
  function validate() {
    $errors = array();
    $relationships = $this->view->display_handler->get_option('relationships');

    $base = $this->view->base_table;

    // If we are based on {node} we need {files}
    $needed_relationship = '';
    if ($base == 'node') {
      $needed_relationship = 'image_files';
    }
    // If we are based on {files} we need {node}
    else if ($base == 'files') {
      $needed_relationship = 'image_node';
    }

    // Does our needed relationship exist?
    if (!empty($needed_relationship) && !isset($relationships[$needed_relationship])) {
      $field = $this->definition['group'] .': '. $this->definition['title'];
      $fields = views_fetch_fields($base, 'relationship');
      $relationship = $fields["$base.$needed_relationship"]['group'] .': '. $fields["$base.$needed_relationship"]['title'];

      $errors[] = t('%field field requires %relation relationship to work. Add this relationship and try again.', array('%field' => $field, '%relation' => $relationship));
    }

    return $errors;
  }

  /**
   * Returns field html.
   */
  function render($values) {
    $image_html = $this->render_html($values);

    if ($this->options['link_to_node']) {
      $image_html = l($image_html, $this->image_url($values), array('html' => TRUE));
    }

    return $image_html;
  }

  /**
   * Returns image html.
   */
  function render_html($values) {
    $image_size = $values->{$this->aliases['image_size']};

    $node = $this->build_image_display_node($values);
    return image_display($node, $image_size);
  }

  /**
   * Builds URL to image based on given values and field options.
   */
  function image_url($values) {
    $image_nid = $values->{$this->aliases['image_nid']};
    $base_nid = $values->{$this->aliases['image_base_nid']};

    $url = '';
    if ($this->options['which_node'] == 'image_node') {
      $url = 'node/'. $image_nid;
    }
    else if ($this->options['which_node'] == 'base_node') {
      $url = 'node/'. $base_nid;
    }

    return $url;
  }

  /**
   * Builds a pseudo image node suitable for use by image_display() instead
   * of using the expensive node_load().
   */
  function build_image_display_node($values) {
    // @todo: Is this the right balance for the lightweight-ness of this?
    //   - Derivatives do not get built.

    $node = new stdClass();
    $node->nid = $values->{$this->aliases['image_nid']};
    $node->title = $values->{$this->aliases['image_title']};
    $node->images = array(
      // Image size => Filepath for given size
      $values->{$this->aliases['image_size']} => $values->{$this->aliases['image_filepath']},
    );

    return $node;
  }
}


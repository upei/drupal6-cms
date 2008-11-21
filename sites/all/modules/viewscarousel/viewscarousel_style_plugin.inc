<?php
// $Id: viewscarousel_style_plugin.inc,v 1.2 2008/11/19 02:17:34 mfer Exp $
/**
 * @file
 *  Provide the views carousel plugin object with default options and form.
 */

/**
  * Implementation of views_plugin_style().
  */
class viewscarousel_style_plugin extends views_plugin_style {
  function option_definition() {
    $options = parent::option_definition();
    $options['vertical'] = array('default' => FALSE);
    $options['start'] = array('default' => 1);
    $options['scroll'] = array('default' => 3);
    $options['visible'] = array('default' => NULL);
    $options['animation'] = array('default' => 0);
    $options['easing'] = array('default' => NULL);
    $options['auto'] = array('default' => 0);
    $options['wrap'] = array('default' => NULL);
    $options['skin'] = array('default' => 'ie7');
    return $options;
  }
  
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['skin'] = array(
      '#type' => 'select',
      '#title' => t('Skin'),
      '#default_value' => $this->options['skin'],
      '#options' => array('ie7' => t('ie7'), 'tango' => t('tango'), 'custom' => t('custom')),
    );
    $form['vertical'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display carousel vertically. Default is horizontal.'),
      '#default_value' => $this->options['vertical'],
    );
    $form['start'] = array(
      '#type' => 'textfield',
      '#title' => t('First item to start on'),
      '#size' => 4,
      '#maxlength' => 4,
      '#default_value' => $this->options['start'],
    );
    $form['scroll'] = array(
      '#type' => 'textfield',
      '#title' => t('The number of items to scroll by'),
      '#size' => 4,
      '#maxlength' => 4,
      '#default_value' => $this->options['scroll'],
    );
    $form['visible'] = array(
      '#type' => 'checkbox',
      '#title' => t('Visibility'),
      '#default_value' => $this->options['visible'],
      '#description' => t('If set, the width/height of the items will be calculated and set depending on the width/height of the clipping, so that exactly that number of items will be visible.'),
    );
    $form['animation'] = array(
      '#type' => 'textfield',
      '#title' => t('Speed of animation'),
      '#size' => 10,
      '#maxlength' => 10,
      '#default_value' => $this->options['animation'],
      '#description' => t('This value can be "fast", "slow", or a time in milliseconds. A value of 0 disables the animation.'),
    );
    $form['easing'] = array(
      '#type' => 'textfield',
      '#title' => t('Name of easing effect'),
      '#size' => 10,
      '#maxlength' => 10,
      '#default_value' => $this->options['easing'],
      '#description' => t('See list of options in the <a href="http://docs.jquery.com/effects/animate">jQuery Documentations</a>'),
    );
    $form['auto'] = array(
      '#type' => 'textfield',
      '#title' => t('Autoscrolling'),
      '#size' => 10,
      '#maxlength' => 10,
      '#default_value' => $this->options['auto'],
      '#description' => t('A value in seconds to specify how often to automatically scroll. Default of 0 disables this feature.'),
    );
    $form['wrap'] = array(
      '#type' => 'select',
      '#title' => t('Wrap content'),
      '#default_value' => $this->options['wrap'],
      // 'circular' => t('Circular'), is another option. It has been removed from option list due to a bug in the js.
      '#options' => array(0 => t('Disabled'), 'first' => t('First'), 'last' => t('Last'), 'both' => t('Both')),
    );
  } 
}
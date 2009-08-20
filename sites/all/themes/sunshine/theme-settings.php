<?php

function phptemplate_settings($saved_settings) {

  $settings = array(
    'sunshine_style' => 'blue',
    'sunshine_breadcrumb' => 0,
  	'sunshine_iepngfix' => 0,
    'sunshine_themelogo' => 0,
    'sunshine_suckerfish' => 0,
    'sunshine_usecustomlogosize' => 0,
    'sunshine_logowidth' => '100',
    'sunshine_logoheight' => '100',
  ) + theme_get_settings('sunshine');

  $form['sunshine_style'] = array(
    '#type' => 'select',
    '#title' => t('Style'),
    '#default_value' => $settings['sunshine_style'],
    '#options' => array(
	  
	  'sunshine' => t('Sunshine'),
    ),
  );

  $form['sunshine_themelogo'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use Themed Logo'),
    '#default_value' => $settings['sunshine_themelogo'],
  );

  $form['sunshine_breadcrumb'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show Breadcrumbs'),
    '#default_value' => $settings['sunshine_breadcrumb'],
  );

  $form['sunshine_iepngfix'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use IE PNG Fix'),
    '#default_value' => $settings['sunshine_iepngfix'],
  );
  
  $form['sunshine_suckerfish'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use Suckerfish Menus'),
    '#default_value' => $settings['sunshine_suckerfish'],
  );

  $form['sunshine_usecustomlogosize'] = array(
    '#type' => 'checkbox',
    '#title' => t('Specify Custom Logo Size'),
    '#default_value' => $settings['sunshine_usecustomlogosize'],
  );

  $form['sunshine_logowidth'] = array(
    '#type' => 'textfield',
    '#title' => t('Logo Width'),
    '#default_value' => $settings['sunshine_logowidth'],
    '#size' => 5,
    '#maxlength' => 5,
  );

  $form['sunshine_logoheight'] = array(
    '#type' => 'textfield',
    '#title' => t('Logo Height'),
    '#default_value' => $settings['sunshine_logoheight'],
    '#size' => 5,
    '#maxlength' => 5,
  );

  $form['sunshine_development'] = array(
    '#type' => 'fieldset',
    '#title' => t('Development'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['sunshine_development']['sunshine_theme_development'] = array(
    '#type' => 'checkbox',
    '#title' => t('Theme development'),
    '#description' => t('Generate theme css cache for every page visit. Normally this only happens during clearing cache.'),
    '#default_value' => $settings['sunshine_theme_development'],
  );
  $form['sunshine_development']['sunshine_per_user_cache'] = array(
    '#type' => 'checkbox',
    '#title' => t('Per-user cache'),
    '#description' => t('Generate per-user css cache for authenticated users.'),
    '#default_value' => $settings['sunshine_per_user_cache'],
  );

  return $form;
}



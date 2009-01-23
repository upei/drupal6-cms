<?php

function phptemplate_settings($saved_settings) {

  $settings = theme_get_settings('sunshine');

  $defaults = array(
    'sunshine_style' => 'blue',
    'sunshine_width' => 0,
	'sunshine_fixedwidth' => '850',
    'sunshine_breadcrumb' => 0,
	'sunshine_iepngfix' => 0,
    'sunshine_themelogo' => 0,
	'sunshine_fontfamily' => 0,
    'sunshine_customfont' => '',
    'sunshine_uselocalcontent' => 0,
    'sunshine_localcontentfile' => '',
    'sunshine_leftsidebarwidth' => '25',
    'sunshine_rightsidebarwidth' => '25',
    'sunshine_suckerfish' => 0,
    'sunshine_usecustomlogosize' => 0,
    'sunshine_logowidth' => '100',
    'sunshine_logoheight' => '100',
  );

  $settings = array_merge($defaults, $settings);

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

  $form['sunshine_width'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use Fixed Width'),
    '#default_value' => $settings['sunshine_width'],
  );

  $form['sunshine_fixedwidth'] = array(
    '#type' => 'textfield',
    '#title' => t('Fixed Width Size'),
    '#default_value' => $settings['sunshine_fixedwidth'],
    '#size' => 5,
    '#maxlength' => 5,
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
  
  $form['sunshine_fontfamily'] = array(
    '#type' => 'select',
    '#title' => t('Font Family'),
    '#default_value' => $settings['sunshine_fontfamily'],
    '#options' => array(
     'Arial, Verdana, sans-serif' => t('Arial, Verdana, sans-serif'),
     '"Arial Narrow", Arial, Helvetica, sans-serif' => t('"Arial Narrow", Arial, Helvetica, sans-serif'),
     '"Times New Roman", Times, serif' => t('"Times New Roman", Times, serif'),
     '"Lucida Sans", Verdana, Arial, sans-serif' => t('"Lucida Sans", Verdana, Arial, sans-serif'),
     '"Lucida Grande", Verdana, sans-serif' => t('"Lucida Grande", Verdana, sans-serif'),
     'Tahoma, Verdana, Arial, Helvetica, sans-serif' => t('Tahoma, Verdana, Arial, Helvetica, sans-serif'),
     'Georgia, "Times New Roman", Times, serif' => t('Georgia, "Times New Roman", Times, serif'),
     'Custom' => t('Custom (specify below)'),
    ),
  );

  $form['sunshine_customfont'] = array(
    '#type' => 'textfield',
    '#title' => t('Custom Font-Family Setting'),
    '#default_value' => $settings['sunshine_customfont'],
    '#size' => 40,
    '#maxlength' => 75,
  );

  $form['sunshine_uselocalcontent'] = array(
    '#type' => 'checkbox',
    '#title' => t('Include Local Content File'),
    '#default_value' => $settings['sunshine_uselocalcontent'],
  );

  $form['sunshine_localcontentfile'] = array(
    '#type' => 'textfield',
    '#title' => t('Local Content File Name'),
    '#default_value' => $settings['sunshine_localcontentfile'],
    '#size' => 40,
    '#maxlength' => 75,
  );

  $form['sunshine_leftsidebarwidth'] = array(
    '#type' => 'textfield',
    '#title' => t('Left Sidebar Width'),
    '#default_value' => $settings['sunshine_leftsidebarwidth'],
    '#size' => 5,
    '#maxlength' => 5,
  );

  $form['sunshine_rightsidebarwidth'] = array(
    '#type' => 'textfield',
    '#title' => t('Right Sidebar Width'),
    '#default_value' => $settings['sunshine_rightsidebarwidth'],
    '#size' => 5,
    '#maxlength' => 5,
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

  return $form;
}



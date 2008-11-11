<?php

function phptemplate_settings($saved_settings) {

  $settings = theme_get_settings('newsflash');

  $defaults = array(
    'newsflash_style' => 'blue',
    'newsflash_width' => 0,
	'newsflash_fixedwidth' => '850',
    'newsflash_breadcrumb' => 0,
	'newsflash_iepngfix' => 0,
    'newsflash_themelogo' => 0,
	'newsflash_fontfamily' => 0,
    'newsflash_customfont' => '',
    'newsflash_uselocalcontent' => 0,
    'newsflash_localcontentfile' => '',
    'newsflash_leftsidebarwidth' => '25',
    'newsflash_rightsidebarwidth' => '25',
    'newsflash_suckerfish' => 0,
    'newsflash_usecustomlogosize' => 0,
    'newsflash_logowidth' => '100',
    'newsflash_logoheight' => '100',
  );

  $settings = array_merge($defaults, $settings);

  $form['newsflash_style'] = array(
    '#type' => 'select',
    '#title' => t('Style'),
    '#default_value' => $settings['newsflash_style'],
    '#options' => array(
	  'copper' => t('Copper'),
	  'green' => t('Green'),
      'blue' => t('Blue'),
	  'black' => t('Black'),
	  'red' => t('Red'),
	  'violet' => t('Violet'),
	  'aqua' => t('Aqua'),
    ),
  );

  $form['newsflash_themelogo'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use Themed Logo'),
    '#default_value' => $settings['newsflash_themelogo'],
  );

  $form['newsflash_width'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use Fixed Width'),
    '#default_value' => $settings['newsflash_width'],
  );

  $form['newsflash_fixedwidth'] = array(
    '#type' => 'textfield',
    '#title' => t('Fixed Width Size'),
    '#default_value' => $settings['newsflash_fixedwidth'],
    '#size' => 5,
    '#maxlength' => 5,
  );

  $form['newsflash_breadcrumb'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show Breadcrumbs'),
    '#default_value' => $settings['newsflash_breadcrumb'],
  );

  $form['newsflash_iepngfix'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use IE PNG Fix'),
    '#default_value' => $settings['newsflash_iepngfix'],
  );
  
  $form['newsflash_fontfamily'] = array(
    '#type' => 'select',
    '#title' => t('Font Family'),
    '#default_value' => $settings['newsflash_fontfamily'],
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

  $form['newsflash_customfont'] = array(
    '#type' => 'textfield',
    '#title' => t('Custom Font-Family Setting'),
    '#default_value' => $settings['newsflash_customfont'],
    '#size' => 40,
    '#maxlength' => 75,
  );

  $form['newsflash_uselocalcontent'] = array(
    '#type' => 'checkbox',
    '#title' => t('Include Local Content File'),
    '#default_value' => $settings['newsflash_uselocalcontent'],
  );

  $form['newsflash_localcontentfile'] = array(
    '#type' => 'textfield',
    '#title' => t('Local Content File Name'),
    '#default_value' => $settings['newsflash_localcontentfile'],
    '#size' => 40,
    '#maxlength' => 75,
  );

  $form['newsflash_leftsidebarwidth'] = array(
    '#type' => 'textfield',
    '#title' => t('Left Sidebar Width'),
    '#default_value' => $settings['newsflash_leftsidebarwidth'],
    '#size' => 5,
    '#maxlength' => 5,
  );

  $form['newsflash_rightsidebarwidth'] = array(
    '#type' => 'textfield',
    '#title' => t('Right Sidebar Width'),
    '#default_value' => $settings['newsflash_rightsidebarwidth'],
    '#size' => 5,
    '#maxlength' => 5,
  );

  $form['newsflash_suckerfish'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use Suckerfish Menus'),
    '#default_value' => $settings['newsflash_suckerfish'],
  );

  $form['newsflash_usecustomlogosize'] = array(
    '#type' => 'checkbox',
    '#title' => t('Specify Custom Logo Size'),
    '#default_value' => $settings['newsflash_usecustomlogosize'],
  );

  $form['newsflash_logowidth'] = array(
    '#type' => 'textfield',
    '#title' => t('Logo Width'),
    '#default_value' => $settings['newsflash_logowidth'],
    '#size' => 5,
    '#maxlength' => 5,
  );

  $form['newsflash_logoheight'] = array(
    '#type' => 'textfield',
    '#title' => t('Logo Height'),
    '#default_value' => $settings['newsflash_logoheight'],
    '#size' => 5,
    '#maxlength' => 5,
  );

  return $form;
}



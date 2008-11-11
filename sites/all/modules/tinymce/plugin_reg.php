<?php
// $Id: plugin_reg.php,v 1.11 2006/05/06 20:09:44 m3avrck Exp $

/**
 * @file
 * Registers TinyMCE plugins for the Drupal TinyMCE module. Note these settings
 * can be overridden by each Drupal theme.
 */

function _tinymce_plugins() {

/**
 * A couple of notes about adding plugins.
 *
 * 1) Don't use any of the *_add or *_add_before hooks for theme button placement.
 *    Stick with theme_advanced_buttons1, theme_advanced_buttons2,
 *    theme_advanced_buttons3 only.
 *
 * 2) You can change the order of the buttons by moving the plugins around in
 * this code. You can also change the order of the button array for each plugin.
 */

$plugins['advhr'] = array();
$plugins['advhr']['theme_advanced_buttons3']  = array('advhr');
$plugins['advhr']['extended_valid_elements']  = array('hr[class|width|size|noshade]');

$plugins['advimage'] = array();
$plugins['advimage']['extended_valid_elements'] = array('img[class|src|alt|title|hspace|vspace|width|height|align|onmouseover|onmouseout|name]');

$plugins['advlink'] = array();
$plugins['advlink']['extended_valid_elements'] = array('a[name|href|target|title|onclick]');

$plugins['autosave'] = array();

$plugins['contextmenu'] = array();

// Note this isn't a true plugin, rather it's buttons made available by the advanced theme.
$plugins['default'] = array();
$plugins['default']['theme_advanced_buttons1'] = array('bold', 'italic', 'underline', 'strikethrough', 'justifyleft', 'justifycenter', 'justifyright', 'justifyfull', 'bullist', 'numlist', 'outdent', 'indent', 'undo', 'redo', 'link', 'unlink', 'anchor');
$plugins['default']['theme_advanced_buttons2'] = array('image', 'cleanup', 'forecolor', 'backcolor', 'sup', 'sub', 'code', 'hr');
$plugins['default']['theme_advanced_buttons3'] = array('cut', 'copy', 'paste', 'visualaid', 'removeformat', 'charmap', 'help');

$plugins['directionality'] = array();
$plugins['directionality']['theme_advanced_buttons3'] = array('ltr', 'rtl');

$plugins['emotions'] = array();
$plugins['emotions']['theme_advanced_buttons3'] = array('emotions');

$plugins['filemanager'] = array();

$plugins['flash'] = array();
$plugins['flash']['theme_advanced_buttons3'] = array('flash');
$plugins['flash']['extended_valid_elements'] = array('img[class|src|alt|title|hspace|vspace|width|height|align|onmouseover|onmouseout|name|obj|param|embed]');

// Note this isn't a true plugin, rather it's buttons made available by the advanced theme.
$plugins['font'] = array();
$plugins['font']['theme_advanced_buttons1'] = array('formatselect', 'fontselect', 'fontsizeselect', 'styleselect');
$plugins['font']['extended_valid_elements'] = array('font[face|size|color|style],span[class|align|style]');

$plugins['fullscreen'] = array();
$plugins['fullscreen']['theme_advanced_buttons3'] = array('fullscreen');

$plugins['iespell'] = array();
$plugins['iespell']['theme_advanced_buttons3'] = array('iespell');

$plugins['imagemanager'] = array();

$plugins['inlinepopups'] = array();

$plugins['insertdatetime'] = array();
$plugins['insertdatetime']['theme_advanced_buttons2'] = array('insertdate', 'inserttime');
$plugins['insertdatetime']['plugin_insertdate_dateFormat'] = array('%Y-%m-%d');
$plugins['insertdatetime']['plugin_insertdate_timeFormat'] = array('%H:%M:%S');

$plugins['layer'] = array();
$plugins['layer']['theme_advanced_buttons3'] = array('insertlayer', 'moveforward', 'movebackward', 'absolute');

$plugins['paste'] = array();
$plugins['paste']['theme_advanced_buttons3'] = array('pastetext', 'pasteword', 'selectall');

$plugins['preview'] = array();
$plugins['preview']['theme_advanced_buttons2'] = array('preview');

$plugins['print'] = array();
$plugins['print']['theme_advanced_buttons3'] = array('print');

$plugins['searchreplace'] = array();
$plugins['searchreplace']['theme_advanced_buttons2'] = array('search', 'replace');

 
if (is_dir(drupal_get_path('module', 'tinymce') . '/tinymce/jscripts/tiny_mce/plugins/spellchecker/')) {
  $plugins['spellchecker'] = array();
  $plugins['spellchecker']['theme_advanced_buttons3'] = array('spellchecker');
}

$plugins['style'] = array();
$plugins['style']['theme_advanced_buttons3'] = array('styleprops');

$plugins['table'] = array();
$plugins['table']['theme_advanced_buttons3'] = array('tablecontrols');

$plugins['zoom'] = array();
$plugins['zoom']['theme_advanced_buttons2'] = array('zoom');

return $plugins;
}

<?php
// $Id: fckeditor.inc,v 1.5 2008/10/13 23:02:29 sun Exp $


/**
 * Plugin implementation of hook_editor().
 *
 * - Function signature and returned editor name nust match include filename.
 * - Returns an array of supported editor versions along with support files.
 *
 * @todo wysiwyg_<editor>_alter() to add/inject optional libraries like gzip.
 */
function wysiwyg_fckeditor_editor() {
  $editor = array();
  $editor['fckeditor'] = array(
    // Required properties
    'title' => 'FCKeditor',
    'vendor url' => 'http://www.fckeditor.net',
    'download url' => 'http://www.fckeditor.net/download',
    'library path' => wysiwyg_get_path('fckeditor'),
    'libraries' => array( // We cannot assume that all editors need just one js library.
      '' => array( // Key may be used in wysiwyg_fckeditor_settings() for exec mode.
        'title' => 'Default',
        'files' => array('fckeditor.js'),
      ),
    ),
    'version callback' => 'wysiwyg_fckeditor_version',
    'themes callback' => 'wysiwyg_fckeditor_themes',
    'settings callback' => 'wysiwyg_fckeditor_settings',
    'plugin callback' => 'wysiwyg_fckeditor_plugins',
    'plugin settings callback' => 'wysiwyg_fckeditor_plugin_settings',
    'versions' => array( // Each version can override global editor properties.
      2.6 => array(
        // 'include files' => array('fckeditor-2.inc'),
        'js files' => array('fckeditor-2.6.js'),
      ),
    ),
    // Optional properties
    // 'editor path' => wysiwyg_get_path('fckeditor'),
    // 'js path' => wysiwyg_get_path('js'),
    // 'css path' => wysiwyg_get_path('css'),
    // @todo Not yet implemented.
    // 'css files' => array('fckeditor.css'),
  );
  return $editor;
}

/**
 * Detect editor version.
 *
 * @param $editor
 *   An array containing editor properties as returned from hook_editor().
 *
 * @return
 *   The installed editor version.
 */
function wysiwyg_fckeditor_version($editor) {
  $library = $editor['library path'] .'/fckeditor.js';
  $library = fopen($library, 'r');
  while ($line = fgets($library, 60)) {
    if (preg_match('@^FCKeditor.prototype.Version\s*= \'([\d\.]+)@', $line, $version)) {
      fclose($library);
      return $version[1];
    }
  }
}

/**
 * Return runtime editor settings for a given wysiwyg profile.
 *
 * @param $editor
 *   A processed hook_editor() array of editor properties.
 * @param $config
 *   An array containing wysiwyg editor profile settings.
 * @param $theme
 *   The name of a theme/GUI/skin to use.
 *
 * @return
 *   A settings array to be populated in
 *   Drupal.settings.wysiwyg.configs.{editor}
 */
function wysiwyg_fckeditor_settings($editor, $config, $theme) {
  $init = array(
    'BasePath' => base_path() . $editor['editor path'] .'/',
    'SkinPath' => base_path() . $editor['editor path'] .'/editor/skins/default/',
    'Width' => '100%',
    'Height' => 420,
    'DefaultLanguage' => 'en',
    'AutoDetectLanguage' => TRUE,
    'ToolbarStartExpanded' => TRUE,
    'EnterMode' => 'p',
    'ShiftEnterMode' => 'br',
    'FontFormats' => strtr($config['block_formats'], array(',' => ';')),
    'FormatSource' => $config['apply_source_formatting'],
    'FormatOutput' => $config['preformatted'],
    'LinkBrowser' => FALSE,
    'LinkUpload' => FALSE,
    'ImageBrowser' => FALSE,
    'ImageUpload' => FALSE,
    'FlashBrowser' => FALSE,
    'FlashUpload' => FALSE,
  );

  if ($config['css_setting'] == 'theme') {
    $css = path_to_theme() .'/style.css';
    if (file_exists($css)) {
      $init['EditorAreaCSS'] = base_path() . $css;
    }
  }
  else if ($config['css_setting'] == 'self') {
    $init['EditorAreaCSS'] = strtr($config['css_path'], array('%b' => base_path(), '%t' => path_to_theme()));
  }

  return $init;
}

/**
 * Determine available editor themes or check/reset a given one.
 *
 * @param $editor
 *   A processed hook_editor() array of editor properties.
 * @param $profile
 *   A wysiwyg editor profile.
 *
 * @return
 *   An array of theme names. The first returned name should be the default
 *   theme name.
 */
function wysiwyg_fckeditor_themes($editor, $profile) {
  return array('default', 'office2003', 'silver');
}

/**
 * Build a JS settings array of external plugins that need to be loaded separately.
 *
 * TinyMCE requires that external plugins (i.e. not residing in the editor's
 * directory) are loaded (once) after the editor has been initialized.
 */
function wysiwyg_fckeditor_plugin_settings($editor, $profile, $info) {
  $plugins = array();
  return $plugins;
}

/**
 * Return internal plugins for FCKeditor; semi-implementation of hook_wysiwyg_plugin().
 */
function wysiwyg_fckeditor_plugins($editor) {
  return array(
  );
}


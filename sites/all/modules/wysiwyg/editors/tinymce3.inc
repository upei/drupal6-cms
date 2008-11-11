<?php
// $Id: tinymce.inc,v 1.8 2008/10/14 21:45:10 sun Exp $


/**
 * Plugin implementation of hook_editor().
 *
 * - Function signature and returned editor name nust match include filename.
 * - Returns an array of supported editor versions along with support files.
 *
 * @todo wysiwyg_<editor>_alter() to add/inject optional libraries like gzip.
 */
function wysiwyg_tinymce3_editor() {
  $editor = array();
  $editor['tinymce'] = array(
    // Required properties
    'title' => 'TinyMCE',
    'vendor url' => 'http://tinymce.moxiecode.com',
    'download url' => 'http://tinymce.moxiecode.com/download.php',
    'library path' => wysiwyg_get_path('tinymce3') . '/jscripts/tiny_mce',
    'libraries' => array( // We cannot assume that all editors need just one js library.
      '' => array( // Key may be used in wysiwyg_tinymce3_settings() for exec mode.
        'title' => 'Minified',
        'files' => array('tiny_mce.js'),
      ),
      'src' => array(
        'title' => 'Source',
        'files' => array('tiny_mce_src.js'),
      ),
    ),
    'version callback' => 'wysiwyg_tinymce3_version',
    'themes callback' => 'wysiwyg_tinymce3_themes',
    'settings callback' => 'wysiwyg_tinymce3_settings',
    'plugin callback' => 'wysiwyg_tinymce3_plugins',
    'plugin settings callback' => 'wysiwyg_tinymce3_plugin_settings',
    'versions' => array( // Each version can override global editor properties.
      '2.1' => array(
        // 'include files' => array('tinymce-2.inc'),
        'js files' => array('tinymce-2.js'),
        'download url' => 'http://sourceforge.net/project/showfiles.php?group_id=103281&package_id=111430&release_id=557383',
      ),
      '3.2' => array(
        // 'include files' => array('tinymce-3.inc'),
        'js files' => array('tinymce-3.js'),
        // 'plugin callback' => 'wysiwyg_tinymce3_3_plugins',
        'libraries' => array(
          '' => array(
            'title' => 'Minified',
            'files' => array('tiny_mce.js'),
          ),
          'jquery' => array(
            'title' => 'jQuery',
            'files' => array('tiny_mce_jquery.js'),
          ),
          'src' => array(
            'title' => 'Source',
            'files' => array('tiny_mce_src.js'),
          ),
        ),
      ),
    ),
    // Optional properties
    // 'editor path' => wysiwyg_get_path('tinymce'), // Assumed by default.
    // 'js path' => wysiwyg_get_path('editors/js'), // Assumed by default.
    // 'css path' => wysiwyg_get_path('editors/css'), // Assumed by default.
    // @todo Not yet implemented.
    // 'css files' => array('tinymce.css'),
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
function wysiwyg_tinymce3_version($editor) {
  $changelog = wysiwyg_get_path('tinymce3') . '/changelog.txt';
  if (!file_exists($changelog)) {
    $changelog = wysiwyg_get_path('tinymce3') . '/changelog';
  }
  $changelog = fopen($changelog, 'r');
  $line = fgets($changelog, 50);
  if (preg_match('@^Version ([\d\.]+)@', $line, $version)) {
    fclose($changelog);
    return $version[1];
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
function wysiwyg_tinymce3_settings($editor, $config, $theme) {
  $init = array(
    'apply_source_formatting' => $config['apply_source_formatting'],
    'button_tile_map' => TRUE, // @todo Add a setting for this.
    'convert_fonts_to_spans' => $config['convert_fonts_to_spans'],
    'document_base_url' => base_path(),
    'entity_encoding' => 'raw',
    'language' => $config['language'],
    'mode' => 'none',
    'paste_auto_cleanup_on_paste' => $config['paste_auto_cleanup_on_paste'],
    'plugins' => array(),
    'preformatted' => $config['preformatted'],
    'relative_urls' => FALSE,
    'remove_linebreaks' => $config['remove_linebreaks'],
    'theme' => $theme,
    'verify_html' => $config['verify_html'],
  );

  if ($config['css_classes']) {
    $init['theme_advanced_styles'] = implode(';', array_filter(explode("\n", str_replace("\r", '', $config['css_classes']))));
  }

  if ($config['css_setting'] == 'theme') {
    $css = path_to_theme() .'/style.css';
    if (file_exists($css)) {
      $init['content_css'] = base_path() . $css;
    }
  }
  else if ($config['css_setting'] == 'self') {
    $init['content_css'] = strtr($config['css_path'], array('%b' => base_path(), '%t' => path_to_theme()));
  }

  // Find the enabled buttons and the button row they belong on.
  // Also map the plugin metadata for each button.
  // @todo What follows is a pain; needs a rewrite.
  if (!empty($config['buttons']) && is_array($config['buttons'])) {
    // $init['buttons'] are stacked into $init['theme_advanced_buttons1'] later.
    // @todo Add a toolbar designer based on jQuery UI.
    $init['buttons'] = array();
    // Only array keys in $init['extensions'] matter; added to $init['plugins']
    // later.
    $init['extensions'] = array();
    // $init['extended_valid_elements'] are just stacked, unique'd later, and
    // transformed into a comma-separated string in wysiwyg_add_editor_settings().
    // @todo Needs a complete plugin API redesign using arrays for
    //   tag => attributes definitions and array_merge_recursive().
    $init['extended_valid_elements'] = array();

    $plugins = wysiwyg_get_plugins($editor['name']);
    foreach ($config['buttons'] as $plugin => $buttons) {
      foreach ($buttons as $button => $enabled) {
        // Iterate separately over buttons and extensions properties.
        foreach (array('buttons', 'extensions') as $type) {
          // Skip unavailable plugins.
          if (!isset($plugins[$plugin][$type][$button])) {
            continue;
          }
          // Add buttons.
          if ($type == 'buttons') {
            $init['buttons'][] = $button;
          }
          // Add external plugins to the list of extensions.
          if ($type == 'buttons' && !isset($plugins[$plugin]['internal'])) {
            $init['extensions'][_wysiwyg_tinymce3_plugin_name('add', $plugin)] = 1;
          }
          // Add internal buttons that also need to be loaded as extension.
          else if ($type == 'buttons' && isset($plugins[$plugin]['load'])) {
            $init['extensions'][$plugin] = 1;
          }
          // Add plain extensions.
          else if ($type == 'extensions') {
            $init['extensions'][$plugin] = 1;
          }
          // Allow plugins to add valid HTML elements.
          if (!empty($plugins[$plugin]['extended_valid_elements'])) {
            $init['extended_valid_elements'] = array_merge($init['extended_valid_elements'], $plugins[$plugin]['extended_valid_elements']);
          }
          // Allow plugins to add or override global configuration settings.
          if (!empty($plugins[$plugin]['options'])) {
            $init = array_merge($init, $plugins[$plugin]['options']);
          }
        }
      }
    }
    // Clean-up.
    $init['extended_valid_elements'] = array_unique($init['extended_valid_elements']);
    if ($init['extensions']) {
      $init['plugins'] = array_keys($init['extensions']);
      unset($init['extensions']);
    } else {
      unset($init['extensions']);
    }
  }

  // Add theme-specific settings.
  switch ($theme) {
    case 'advanced':
      $init += array(
        'theme_advanced_blockformats' => $config['block_formats'] ? $config['block_formats'] : 'p,h2,h3,h4,h5,h6',
        'theme_advanced_path_location' => $config['path_loc'],
        'theme_advanced_resizing' => $config['resizing'],
        'theme_advanced_resize_horizontal' => FALSE,
        'theme_advanced_resizing_use_cookie' => FALSE,
        'theme_advanced_toolbar_location' => $config['toolbar_loc'],
        'theme_advanced_toolbar_align' => $config['toolbar_align'],
        // Note: These rows need to be set to NULL otherwise TinyMCE loads its
        // own buttons as defined in advanced theme.
        'theme_advanced_buttons1' => array(),
        'theme_advanced_buttons2' => array(),
        'theme_advanced_buttons3' => array(),
      );

      for ($i = 0; $i < count($init['buttons']); $i++) {
        $init['theme_advanced_buttons1'][] = $init['buttons'][$i];
      }
      break;
  }
  unset($init['buttons']);

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
function wysiwyg_tinymce3_themes($editor, $profile) {
  /*
  $themes = array();
  $dir = $editor['library path'] . '/themes/';
  if (is_dir($dir) && $dh = opendir($dir)) {
    while (($file = readdir($dh)) !== FALSE) {
      if (!in_array($file, array('.', '..', 'CVS', '.svn')) && is_dir($dir . $file)) {
        $themes[$file] = $file;
      }
    }
    closedir($dh);
    asort($themes);
  }
  return $themes;
  */
  return array('advanced', 'simple');
}

/**
 * Build a JS settings array of external plugins that need to be loaded separately.
 *
 * TinyMCE requires that external plugins (i.e. not residing in the editor's
 * directory) are loaded (once) after the editor has been initialized.
 */
function wysiwyg_tinymce3_plugin_settings($editor, $profile, $plugins) {
  $settings = array();
  foreach ($plugins as $name => $plugin) {
    if (!isset($plugin['internal'])) {
      $settings[$name] = base_path() . $plugin['path'];
    }
  }
  return $settings;
}

/**
 * Add or remove leading hiven to/of external plugin names.
 *
 * TinyMCE requires that external plugins, which should not be loaded from
 * its own plugin repository are prefixed with a hiven in the name.
 * 
 * @param string $op
 *   Operation to perform, 'add' or 'remove' (hiven).
 * @param string $name
 *   A plugin name.
 */
function _wysiwyg_tinymce3_plugin_name($op, $name) {
  if ($op == 'add') {
    if (strpos($name, '-') !== 0) {
      return '-'. $name;
    }
    return $name;
  }
  else if ($op == 'remove') {
    if (strpos($name, '-') === 0) {
      return substr($name, 1);
    }
    return $name;
  }
}

/**
 * Return internal plugins for TinyMCE; semi-implementation of hook_wysiwyg_plugin().
 */
function wysiwyg_tinymce3_plugins($editor) {
  return array(
    'default' => array(
      'path' => $editor['library path'] .'/themes/advanced',
      'buttons' => array(
        'bold' => t('Bold'), 'italic' => t('Italic'), 'underline' => t('Underline'),
        'strikethrough' => t('Strike-through'),
        'justifyleft' => t('Align left'), 'justifycenter' => t('Align center'), 'justifyright' => t('Align right'), 'justifyfull' => t('Justify'),
        'bullist' => t('Bullet list'), 'numlist' => t('Numbered list'),
        'outdent' => t('Outdent'), 'indent' => t('Indent'),
        'undo' => t('Undo'), 'redo' => t('Redo'),
        'link' => t('Link'), 'unlink' => t('Unlink'), 'anchor' => t('Anchor'),
        'image' => t('Image'),
        'cleanup' => t('Clean-up'),
        'forecolor' => t('Forecolor'), 'backcolor' => t('Backcolor'),
        'sup' => t('Sup'), 'sub' => t('Sub'),
        'blockquote' => t('Blockquote'), 'code' => t('Source code'),
        'hr' => t('Horizontal rule'),
        'cut' => t('Cut'), 'copy' => t('Copy'), 'paste' => t('Paste'),
        'visualaid' => t('Visual aid'),
        'removeformat' => t('Remove format'),
        'charmap' => t('Character map'),
        'help' => t('Help')),
      'internal' => TRUE,
    ),
    'advhr' => array(
      'path' => $editor['library path'] .'/plugins/advhr',
      'buttons' => array('advhr' => t('Advanced horizontal rule')),
      'extended_valid_elements' => array('hr[class|width|size|noshade]'),
      'url' => 'http://wiki.moxiecode.com/index.php/TinyMCE:Plugins/advhr',
      'internal' => TRUE,
      'load' => TRUE,
    ),
    'advimage' => array(
      'path' => $editor['library path'] .'/plugins/advimage',
      'extensions' => array('advimage' => t('Advanced image')),
      'extended_valid_elements' => array('img[class|src|alt|title|hspace|vspace|width|height|align|onmouseover|onmouseout|name]'),
      'url' => 'http://wiki.moxiecode.com/index.php/TinyMCE:Plugins/advimage',
      'internal' => TRUE,
      'load' => TRUE,
    ),
    'advlink' => array(
      'path' => $editor['library path'] .'/plugins/advlink',
      'extensions' => array('advlink' => t('Advanced link')),
      'extended_valid_elements' => array('a[name|href|target|title|onclick]'),
      'url' => 'http://wiki.moxiecode.com/index.php/TinyMCE:Plugins/advlink',
      'internal' => TRUE,
      'load' => TRUE,
    ),
    'autosave' => array(
      'path' => $editor['library path'] .'/plugins/autosave',
      'extensions' => array('autosave' => t('Auto save')),
      'url' => 'http://wiki.moxiecode.com/index.php/TinyMCE:Plugins/autosave',
      'internal' => TRUE,
      'load' => TRUE,
    ),
    'contextmenu' => array(
      'path' => $editor['library path'] .'/plugins/contextmenu',
      'extensions' => array('contextmenu' => t('Context menu')),
      'url' => 'http://wiki.moxiecode.com/index.php/TinyMCE:Plugins/contextmenu',
      'internal' => TRUE,
    ),
    'directionality' => array(
      'path' => $editor['library path'] .'/plugins/directionality',
      'buttons' => array('ltr' => t('Left-to-right'), 'rtl' => t('Right-to-left')),
      'url' => 'http://wiki.moxiecode.com/index.php/TinyMCE:Plugins/directionality',
      'internal' => TRUE,
      'load' => TRUE,
    ),
    'emotions' => array(
      'path' => $editor['library path'] .'/plugins/emotions',
      'buttons' => array('emotions' => t('Emotions')),
      'url' => 'http://wiki.moxiecode.com/index.php/TinyMCE:Plugins/emotions',
      'internal' => TRUE,
      'load' => TRUE,
    ),
    'flash' => array(
      'path' => $editor['library path'] .'/plugins/flash',
      'buttons' => array('flash' => t('Flash')),
      'extended_valid_elements' => array('img[class|src|alt|title|hspace|vspace|width|height|align|onmouseover|onmouseout|name|obj|param|embed]'),
      'url' => 'http://wiki.moxiecode.com/index.php/TinyMCE:Plugins/flash',
      'internal' => TRUE,
      'load' => TRUE,
    ),
    'font' => array(
      'path' => $editor['library path'] .'/plugins/font',
      'buttons' => array('formatselect' => t('HTML block format'), 'fontselect' => t('Font'), 'fontsizeselect' => t('Font size'), 'styleselect' => t('Font style')),
      'extended_valid_elements' => array('font[face|size|color|style],span[class|align|style]'),
      'url' => 'http://wiki.moxiecode.com/index.php/TinyMCE:Plugins/font',
      'internal' => TRUE,
    ),
    'fullscreen' => array(
      'path' => $editor['library path'] .'/plugins/fullscreen',
      'buttons' => array('fullscreen' => t('Fullscreen')),
      'url' => 'http://wiki.moxiecode.com/index.php/TinyMCE:Plugins/fullscreen',
      'internal' => TRUE,
      'load' => TRUE,
    ),
    'inlinepopups' => array(
      'path' => $editor['library path'] .'/plugins/inlinepopups',
      'extensions' => array('inlinepopups' => t('Inline popups')),
      'options' => array(
        'dialog_type' => array('modal'),
      ),
      'url' => 'http://wiki.moxiecode.com/index.php/TinyMCE:Plugins/inlinepopups',
      'internal' => TRUE,
      'load' => TRUE,
    ),
    'insertdatetime' => array(
      'path' => $editor['library path'] .'/plugins/insertdatetime',
      'buttons' => array('insertdate' => t('Insert date'), 'inserttime' => t('Insert time')),
      'options' => array(
        'plugin_insertdate_dateFormat' => array('%Y-%m-%d'),
        'plugin_insertdate_timeFormat' => array('%H:%M:%S'),
      ),
      'url' => 'http://wiki.moxiecode.com/index.php/TinyMCE:Plugins/insertdatetime',
      'internal' => TRUE,
      'load' => TRUE,
    ),
    'layer' => array(
      'path' => $editor['library path'] .'/plugins/layer',
      'buttons' => array('insertlayer' => t('Insert layer'), 'moveforward' => t('Move forward'), 'movebackward' => t('Move backward'), 'absolute' => t('Absolute')),
      'url' => 'http://wiki.moxiecode.com/index.php/TinyMCE:Plugins/layer',
      'internal' => TRUE,
      'load' => TRUE,
    ),
    'paste' => array(
      'path' => $editor['library path'] .'/plugins/paste',
      'buttons' => array('pastetext' => t('Paste text'), 'pasteword' => t('Paste from Word'), 'selectall' => t('Select all')),
      'url' => 'http://wiki.moxiecode.com/index.php/TinyMCE:Plugins/paste',
      'internal' => TRUE,
      'load' => TRUE,
    ),
    'preview' => array(
      'path' => $editor['library path'] .'/plugins/preview',
      'buttons' => array('preview' => t('Preview')),
      'url' => 'http://wiki.moxiecode.com/index.php/TinyMCE:Plugins/preview',
      'internal' => TRUE,
      'load' => TRUE,
    ),
    'print' => array(
      'path' => $editor['library path'] .'/plugins/print',
      'buttons' => array('print' => t('Print')),
      'url' => 'http://wiki.moxiecode.com/index.php/TinyMCE:Plugins/print',
      'internal' => TRUE,
      'load' => TRUE,
    ),
    'searchreplace' => array(
      'path' => $editor['library path'] .'/plugins/searchreplace',
      'buttons' => array('search' => t('Search'), 'replace' => t('Replace')),
      'url' => 'http://wiki.moxiecode.com/index.php/TinyMCE:Plugins/searchreplace',
      'internal' => TRUE,
      'load' => TRUE,
    ),
    'style' => array(
      'path' => $editor['library path'] .'/plugins/style',
      'buttons' => array('styleprops' => t('Style properties')),
      'url' => 'http://wiki.moxiecode.com/index.php/TinyMCE:Plugins/style',
      'internal' => TRUE,
      'load' => TRUE,
    ),
    'table' => array(
      'path' => $editor['library path'] .'/plugins/table',
      'buttons' => array('tablecontrols' => t('Table')),
      'url' => 'http://wiki.moxiecode.com/index.php/TinyMCE:Plugins/table',
      'internal' => TRUE,
      'load' => TRUE,
    ),
  );
}


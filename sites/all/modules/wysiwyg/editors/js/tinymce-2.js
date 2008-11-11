// $Id: tinymce-2.js,v 1.5 2008/10/13 23:16:50 sun Exp $

/**
 * Initialize editor instances.
 *
 * This function needs to be called before the page is fully loaded, as
 * calling tinyMCE.init() after the page is loaded breaks IE6.
 *
 * @param editorSettings
 *   An object containing editor settings for each enabled editor theme.
 */
Drupal.wysiwyg.editor.init.tinymce = function(editorSettings) {
  // If JS compression is enabled, TinyMCE is unable to find its own base path
  // and exec mode, hence we need to define it manually.
  // @todo Move global library settings somewhere else.
  tinyMCE.baseURL = Drupal.settings.wysiwyg.editorBasePath;
  tinyMCE.srcMode = (Drupal.settings.wysiwyg.execMode == 'src' ? '_src' : '');
  tinyMCE.gzipMode = (Drupal.settings.wysiwyg.execMode == 'gzip');

  // Initialize editor configurations.
  for (var theme in editorSettings) {
    tinyMCE.init(editorSettings[theme]);
  }
  for (var plugin in Drupal.settings.wysiwyg.plugins.tinymce) {
    tinyMCE.loadPlugin(plugin, Drupal.settings.wysiwyg.plugins.tinymce[plugin]);
  }
};

/**
 * Attach this editor to a target element.
 *
 * See Drupal.wysiwyg.editor.attach.none() for a full desciption of this hook.
 */
Drupal.wysiwyg.editor.attach.tinymce = function(context, params, editorSettings) {
  // Configure settings for this theme.
  for (var setting in editorSettings[params.theme]) {
    tinyMCE.settings[setting] = editorSettings[params.theme][setting];
  }
  // Attach editor control if default is on.
  if (Drupal.settings.wysiwyg.status) {
    tinyMCE.execCommand('mceAddControl', true, params.field);
  }
};

/**
 * Detach a single or all editors.
 *
 * See Drupal.wysiwyg.editor.detach.none() for a full desciption of this hook.
 */
Drupal.wysiwyg.editor.detach.tinymce = function(context, params) {
  if (typeof params != 'undefined') {
    tinyMCE.removeMCEControl(tinyMCE.getEditorId(params.field));
    $('#' + params.field).removeAttr('style');
  }
//  else if (tinyMCE.activeEditor) {
//    tinyMCE.triggerSave();
//    tinyMCE.activeEditor.remove();
//  }
};


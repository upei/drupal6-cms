// $Id: jwysiwyg.js,v 1.1 2008/10/28 23:46:27 sun Exp $

/**
 * Attach this editor to a target element.
 */
Drupal.wysiwyg.editor.attach.jwysiwyg = function(context, params, editorSettings) {
  // Attach editor control if default is on.
  if (Drupal.settings.wysiwyg.status) {
    $('#' + params.field).wysiwyg();
  }
};

/**
 * Detach a single or all editors.
 */
Drupal.wysiwyg.editor.detach.jwysiwyg = function(context, params) {
  var $field = $('#' + params.field);
  var editor = $field.data('wysiwyg');
  if (typeof editor != 'undefined') {
    editor.saveContent();
    editor.element.remove();
  }
  $field.removeData('wysiwyg');
  $field.show();
};


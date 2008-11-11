// $Id: nicedit.js,v 1.1 2008/10/30 10:15:20 sun Exp $

/**
 * Attach this editor to a target element.
 */
Drupal.wysiwyg.editor.attach.nicedit = function(context, params, editorSettings) {
  // Attach editor control if default is on.
  if (Drupal.settings.wysiwyg.status) {
    var editor = new nicEditor(editorSettings[params.theme]);
    editor.panelInstance(params.field);
  }
};

/**
 * Detach a single or all editors.
 *
 * See Drupal.wysiwyg.editor.detach.none() for a full desciption of this hook.
 */
Drupal.wysiwyg.editor.detach.nicedit = function(context, params) {
  if (typeof params != 'undefined') {
    var instance = nicEditors.findEditor(params.field);
    if (instance) {
      instance.ne.removeInstance(params.field);
      instance.ne.removePanel();
    }
  }
  else {
    for (var e in nicEditors.editors) {
      // Save contents of all editors back into textareas.
      var instances = nicEditors.editors[e].nicInstances;
      for (var i = 0; i < instances.length; i++) {	
        instances[i].remove();
      }
      // Remove all editor instances.
      nicEditors.editors[e].nicInstances = [];
    }
  }
};


// $Id: fckeditor-2.6.js,v 1.5 2008/10/13 23:02:30 sun Exp $

/**
 * Attach this editor to a target element.
 *
 * See Drupal.wysiwyg.editor.attach.none() for a full desciption of this hook.
 */
Drupal.wysiwyg.editor.attach.fckeditor = function(context, params, settings) {
  var FCKinstance = new FCKeditor(params.field, settings[params.theme]['Width'], settings[params.theme]['Height']);
  // Configure settings for this theme.
  FCKinstance.BasePath = settings[params.theme].BasePath;
  for (var setting in settings[params.theme]) {
    FCKinstance.Config[setting] = settings[params.theme][setting];
  }
  // Attach editor control if default is on.
  if (Drupal.settings.wysiwyg.status) {
    FCKinstance.ReplaceTextarea();
  }
};

/**
 * Detach a single or all editors.
 *
 * See Drupal.wysiwyg.editor.detach.none() for a full desciption of this hook.
 */
Drupal.wysiwyg.editor.detach.fckeditor = function(context, params) {
  if (typeof params != 'undefined') {
    var editor = FCKeditorAPI.GetInstance(params.field);
    if (editor) {
      $('#' + params.field).val(editor.GetXHTML()).show();
      $('#' + params.field + '___Config').remove();
      $('#' + params.field + '___Frame').remove();
      delete FCKeditorAPI.__Instances[params.field];
    }
  }
//  else {
//    tinyMCE.triggerSave();
//    tinyMCE.remove();
//  }
};


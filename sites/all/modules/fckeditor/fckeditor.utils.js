// $Id: fckeditor.utils.js,v 1.2.2.8.2.13 2008/10/16 15:05:02 wwalc Exp $
// map of instancename -> FCKeditor object
var fckInstances = {};
// this object will store teaser information
var fckTeaser = { lookup : {}, lookupSetup : false, cache : {} };

/**
 * Drupal behavior that adds FCKeditors to textareas
 */
Drupal.behaviors.fckeditor = function(context) {
  $('textarea.fckeditor:not(.fckeditor-processed)', context).each(function() {
    var textarea = $(this).addClass('fckeditor-processed');

    var taid = textarea.attr('id');
    if (fckInstances[taid]) {
      var editorInstance = fckInstances[taid];

      if (editorInstance.defaultState == 1) {
        editorInstance.ReplaceTextarea();
        $('#img_assist-link-' + taid).hide();
        $(".img_assist-button").hide();
      }
    }
  });
}

/**
 * This method takes care of replacing a textarea with an FCKeditor
 * and vice versa.
 */
function Toggle(textareaID, TextTextarea, TextRTE)
{
  var swtch = $('#switch_'+textareaID);

  // check if this FCKeditor was initially disabled
  if (fckInstances[textareaID].defaultState == 0) {
    fckInstances[textareaID].defaultState = 2;
    fckInstances[textareaID].ReplaceTextarea();
    swtch.text(TextTextarea);
    $(".img_assist-button").hide();
    // simply return: ReplaceTextarea will take the contents of the textarea for us
    return;
  }

  var textArea = $('#'+textareaID);
  var textAreaContainer = $('#'+textareaID).parents('.resizable-textarea');
  var editorFrame = $('#'+textareaID+'___Frame');
  var editorInstance = FCKeditorAPI.GetInstance(textareaID);
  var text;

  // execute the switch
  if (textArea.is(':hidden')) {
    // switch from fck to textarea
    swtch.text(TextRTE);

    text = editorInstance.GetData(true);

    // check if we have to take care of teasers
    var teaser = FCKeditor_TeaserInfo(textareaID);

    if (teaser) {
      var t = text.indexOf('<!--break-->');
      if (t != -1) {
        teaser.textarea.val(FCKeditor_trim(text.slice(0,t)));
        text = FCKeditor_trim(text.slice(t+12));

        teaser.textareaContainer.show();
        teaser.textarea.attr('disabled', '');
        if (teaser.button.attr('value') != Drupal.t('Join summary')) {
          try {teaser.button.click();} catch(e) {teaser.button.val(Drupal.t('Join summary'));}
        }
      } else {
        teaser.textarea.attr('disabled', 'disabled');
        if (teaser.button.attr('value') != Drupal.t('Split summary at cursor')) {
          try {teaser.button.click();} catch(e) {teaser.button.val(Drupal.t('Split summary at cursor'));}
        }
      }

      teaser.buttonContainer.show();
    } else {
      text = textArea.val();
    }

    textArea.val(text);

    textArea.show();
    textAreaContainer.show();
    editorFrame.hide();
    $('#img_assist-link-' + textareaID).show();
    $(".img_assist-button").show();
    $(textArea).parent().children(".grippie").show();
  } else {
    // switch from textarea to fck
    swtch.text(TextTextarea);

    // check if we have to take care of teasers
    var teaser = FCKeditor_TeaserInfo(textareaID);

    if (teaser) {
      if (teaser.textarea.val().length > 0) {
        text = teaser.textarea.val() + '\n<!--break-->\n' + textArea.val();
      } else {
        text = textArea.val();
      }
      teaser.textarea.attr('disabled', '');
      teaser.buttonContainer.hide();
      teaser.textareaContainer.hide();
      teaser.checkboxContainer.show();
    } else {
      text = textArea.val();
    }

    editorInstance.SetData(text, true);

    // Switch the DIVs display.
    textArea.hide();
    textAreaContainer.show();
    $(editorInstance.LinkedField).parent().children(".grippie").hide();
    editorFrame.show();
    $('#img_assist-link-' + textareaID).hide();
    $(".img_assist-button").hide();
  }
}

/**
 * The FCKeditor_OnComplete function is a special function called everytime an
 * editor instance is completely loaded and available for API interactions.
 */
function FCKeditor_OnComplete(editorInstance) {
  
  // Enable the switch button. It is disabled at startup, waiting the editor to be loaded.
  $('#switch_' + editorInstance.Name).show();
  editorInstance.Events.AttachEvent('OnAfterLinkedFieldUpdate', FCKeditor_OnAfterLinkedFieldUpdate);

  var teaser = FCKeditor_TeaserInfo(editorInstance.Name);

  if (teaser) {
    // if there is a teaser, prepend it to the text, only when switched to FCKeditor using toggle
    //if (fckInstances[editorInstance.Name].defaultState == 2) {
      if (teaser.textarea.val().length > 0) {
        var text = teaser.textarea.val() + '\n<!--break-->\n' + editorInstance.GetData(true);
        editorInstance.SetData(text);
      }
    //}
    // hide the teaser
    teaser.textarea.attr('disabled', '');
    teaser.buttonContainer.hide();
    teaser.textareaContainer.hide();
    teaser.checkboxContainer.show();
  }

  $(editorInstance.LinkedField).parent().children(".grippie").hide();

  // very ugly hack to circumvent FCKeditor from re-updating textareas on submission. We do that ourselves
  // FCKeditor will happily update the fake textarea while we will use the proper one
  editorInstance.LinkedField2 = editorInstance.LinkedField;
  editorInstance.LinkedField = $('<textarea></textarea>');

  // Img_Assist integration
  IntegrateWithImgAssist();
}

/**
 * This method is executed for every FCKeditor instance just after the underlying text field is updated
 * before the form is submitted.
 */
function FCKeditor_OnAfterLinkedFieldUpdate(editorInstance) {
  var textArea = editorInstance.LinkedField2;
  var taid = textArea.id;

  var teaser = FCKeditor_TeaserInfo(taid);

  if ($(textArea).is(':hidden')) {
    var text = editorInstance.GetData(true);
    textArea.value = text;
    // only update the teaser field if this field is associated with a teaser field
    if (teaser) {
      var t = text.indexOf('<!--break-->');
      if (t != -1) {
        teaser.textarea.val(FCKeditor_trim(text.slice(0,t)));
        textArea.value = FCKeditor_trim(text.slice(t+12));
      } else {
        teaser.textarea.val('');
        teaser.textarea.attr('disabled', 'disabled');

        var teaserbuttontxt = Drupal.t('Join summary');

        if (teaser.button.attr('value') == teaserbuttontxt) {
          try {
            teaser.button.click();
          } catch(e) {
            teaserbutton.val(teaserbuttontxt);
          }
        }
      }
    }
  }
}

function IntegrateWithImgAssist()
{
  var link = document.getElementsByTagName("a");
  for (var i = 0; i < link.length; i++) {
    cl = link[i].className;
    if ( cl == "img_assist-link") {
      link[i].href = link[i].href.replace("/load/textarea", "/load/fckeditor");
    }
  }
}

/**
 * Removes leading and trailing whitespace from the input
 */
function FCKeditor_trim(text) {
  return text.replace(/^\s+/g, '').replace(/\s+$/g, '');
}

/**
 * This function retrieves information about a possible teaser field
 * associated with the mentioned field.
 *
 * @param taid string HTML id of the main text area
 */
function FCKeditor_TeaserInfo(taid) {
  // if the result is cached, return it
  if (fckTeaser.cache[taid]) {
    return fckTeaser.cache[taid];
  }

  // build a lookup table
  if (!fckTeaser.lookupSetup) {
    fckTeaser.lookupSetup = true;
    for(var x in Drupal.settings.teaser) {
      fckTeaser.lookup[Drupal.settings.teaser[x]] = x;
    }
  }

  // find the elements
  if (fckTeaser.lookup[taid]) {
    var obj = {
      textarea : $('#'+fckTeaser.lookup[taid]),
      checkbox : $('#'+Drupal.settings.teaserCheckbox[fckTeaser.lookup[taid]])
    };

    obj.textareaContainer = obj.textarea.parent();
    obj.checkboxContainer = obj.checkbox.parent();

    obj.button = $('input.teaser-button', obj.checkbox.parents('div.teaser-checkbox').get(0));
    obj.buttonContainer = obj.button.parent();

    fckTeaser.cache[taid] = obj;
  } else {
    fckTeaser.cache[taid] = null;
  }

  return fckTeaser.cache[taid];
}

/**
 * Creates a screen wide popup window containing an FCKeditor
 */
function FCKeditor_OpenPopup(popupUrl, jsID, textareaID) {
  popupUrl = popupUrl + '?var='+ jsID + '&el=' + textareaID;

  var teaser = FCKeditor_TeaserInfo(textareaID);
  if (teaser) {
    popupUrl = popupUrl + '&teaser=' + teaser.textarea.attr('id');
  }

  window.open(popupUrl, null, 'toolbar=no,location=no,directories=no,status=no,menubar=no,scrollbars=no,resizable=1,dependent=yes');
}

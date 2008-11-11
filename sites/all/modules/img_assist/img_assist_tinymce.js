// $Id: img_assist_tinymce.js,v 1.3.4.1 2008/07/18 22:54:36 sun Exp $
/**
 * This javascript file allows img_assist to work with TinyMCE via the
 * drupalimage plugin for TinyMCE.
 * This file is used instead of img_assist_textarea.js if img_assist is called
 * from the drupalimage plugin.
 * Additional JS files similar to img_assist_textarea.js and
 * img_assist_tinymce.js could be created for using img_assist with other
 * WYSIWYG editors. Some minor code changes to the menu function in
 * img_assist.module will be necessary, at least in img_assist_menu() and
 * img_assist_loader().
 */

// This doesn't work right. tiny_mce_popup.js needs to be loaded BEFORE any
// setWindowArg() commands are issued.
// document.write('<sc'+'ript language="javascript" type="text/javascript" src="' + BASE_URL + 'modules/tinymce/tinymce/jscripts/tiny_mce/tiny_mce_popup.js"><\/script>'); 

// get variables that were passed to this window from the tinyMCE editor
var nid, captionTitle, captionDesc, link, url, align, width, height;

function preinit() {
  tinyMCE.setWindowArg('mce_windowresize', false);
  tinyMCE.setWindowArg('mce_replacevariables', false);
}

function initLoader() {
  nid          =      tinyMCE.getWindowArg('nid');
  captionTitle = '' + tinyMCE.getWindowArg('captionTitle');
  captionDesc  = '' + tinyMCE.getWindowArg('captionDesc');
  link         = '' + tinyMCE.getWindowArg('link');
  url          = '' + tinyMCE.getWindowArg('url');
  align        = '' + tinyMCE.getWindowArg('align');
  width        = '' + tinyMCE.getWindowArg('width');
  height       = '' + tinyMCE.getWindowArg('height');

  if (nid > 0) {
    frames['img_assist_main'].window.location.href = BASE_URL + 'index.php?q=img_assist/properties/' + nid + '/update';
  }
  else {
    frames['img_assist_main'].window.location.href = BASE_URL + 'index.php?q=img_assist/thumbs/img_assist_browser';
  }
}

function initProperties() {
  var formObj = frames['img_assist_main'].document.forms[0];
  if (formObj['edit-update'].value == 1) {
    formObj['edit-title'].value = captionTitle;
    formObj['edit-desc'].value = captionDesc;
    // Backwards compatibility: Also parse link/url in the format link=url,foo.
    if(link.indexOf(',') != -1) {
      link = link.split(',', 2);
      formObj['edit-link'].value = link[0];
      if (link[0] == 'url') {
        formObj['edit-url'].value = link[1];
      }
    }
    else {
      formObj['edit-link'].value = link;
      if(typeof url != 'undefined' && url != '') {
        formObj['edit-url'].value = url;
      }
    }
    formObj['edit-align'].value = align;
    
    // When editing the properties of an image placed with 
    // img_assist, it's not easy to figure out what standard
    // size was used.  Until such code is written we will 
    // just set the size to "other".  Of course, if custom
    // isn't an option then I guess the image size will default
    // back to thumbnail.
    formObj['edit-size-label'].value = "other";
    formObj['edit-width'].value = width;
    formObj['edit-height'].value = height;
  }
  setHeader('properties');
  updateCaption();
  onChangeLink();
  onChangeSizeLabel();
}

function initThumbs() {
  setHeader('browse');
}

function initHeader() {
}

function initUpload() {
  setHeader('uploading');
}

function getFilterTag(formObj) {
  nid          = formObj['edit-nid'].value;
  captionTitle = formObj['edit-title'].value;
  captionDesc  = formObj['edit-desc'].value;
  link         = formObj['edit-link'].value;
  url          = formObj['edit-url'].value;
  align        = formObj['edit-align'].value;
  width        = formObj['edit-width'].value;
  height       = formObj['edit-height'].value;
  
  // Create the image placeholder tag
  // @see TinyMCE_drupalimage_cleanup() in drupalimage plugin.
  // Backwards compatibility: Also parse link/url in the format link=url,foo.
  var miscAttribs = 'nid=' + nid + '|title=' + captionTitle + '|desc=' + captionDesc + '|link=' + link;
  if(typeof url != 'undefined' && url != formObj['edit-default-url'].value) {
    miscAttribs += '|url=' + url;
  }
  miscAttribs = encodeURIComponent(miscAttribs);
  var content = '<img src="' + (tinyMCE.getParam("theme_href") + "/images/spacer.gif") + '"'
              + ' width="' + width + '" height="' + height + '" align="' + align + '"'
              + ' alt="' + miscAttribs + '" title="' + miscAttribs + '"'
              + ' name="mceItemDrupalImage" class="mceItemDrupalImage" />';
  
  return content;
}

function insertToEditor(content) {
  // Insert the image
  tinyMCE.execCommand("mceInsertContent", true, content);
  tinyMCE.selectedInstance.repaint();
  
  // Close the dialog
  tinyMCEPopup.close();
  return false;
}

function cancelAction() {
  // Close the dialog
  tinyMCEPopup.close();
}

// While loading
preinit();

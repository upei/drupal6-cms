//
// Load the img_assist_textarea.js script
//
// Get the header of the document
var head= document.getElementsByTagName('head')[0];
// Create a new script object
var script= document.createElement('script');
script.type= 'text/javascript';
// Source dirname is built from the second script tag found in the document
script.src = head.getElementsByTagName('script')[1].src.match( /.*\// ) + 'img_assist_textarea.js';
// Append the new script to the header
head.appendChild(script);

setTimeout("InitFCKeditorImgAssist();", 1000);

function InitFCKeditorImgAssist() {
  var oldInsertToEditor = insertToEditor;

  insertToEditor = function(content) {

    //handle FCKeditor in popup mode
    if ((myTextarea == '') && (window.opener)) {
      var myDoc = window.opener;
      if (myDoc.oFCKeditor) {
        var inst= myDoc.oFCKeditor.InstanceName;
        var oEditor = myDoc.FCKeditorAPI.GetInstance( inst );
        if (oEditor.EditMode == myDoc.FCK_EDITMODE_WYSIWYG) {
          oEditor.InsertHtml(content) ;
        }
        else {
          alert(Drupal.t('Inserting image into FCKeditor is allowed only in WYSIWYG mode'));
        }
        cancelAction();
        return false;
      }
    }

    //FCKeditor enabled and running == textarea not displayed
    if ( myTextarea.style.display == 'none' ) {
      var opener = window.opener;
      if (opener.fckLaunchedJsId) {
        for( var i = 0 ; i < opener.fckLaunchedJsId.length ; i++ ) {
          if ( opener.fckLaunchedTextareaId[i] == myTextarea.id ) {
            var oEditor = opener.FCKeditorAPI.GetInstance( opener.fckLaunchedJsId[i] );
            if (oEditor.EditMode == opener.FCK_EDITMODE_WYSIWYG) {
              oEditor.InsertHtml(content) ;
            }
            else {
              alert(Drupal.t('Inserting image into FCKeditor is allowed only in WYSIWYG mode'));
            }
          }
        }
      }
      else {
        var oEditor = opener.FCKeditorAPI.GetInstance(myTextarea.id);
        if (oEditor.EditMode == opener.FCK_EDITMODE_WYSIWYG) {
          oEditor.InsertHtml(content) ;
        }
        else {
          alert(Drupal.t('Inserting image into FCKeditor is allowed only in WYSIWYG mode'));
        }
      }
      cancelAction();
      return false;
    }

    oldInsertToEditor(content);
  };
}
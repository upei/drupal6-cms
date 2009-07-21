//
// Load the img_assist_textarea.js script
//
// Get the header of the document
var head= document.getElementsByTagName('head')[0];

function fckeditor_add_script(src) {
  var script= document.createElement('script');
  script.type= 'text/javascript';
  script.src = src;
  head.appendChild(script);
}

// Source dirname is built from the second script tag found in the document
for (var i = 0; i < head.getElementsByTagName('script').length; i++) {
  if ( head.getElementsByTagName('script')[i].src.match( /img_assist/ ) ) {
    fckeditor_add_script(head.getElementsByTagName('script')[i].src.replace( /img_assist[_a-z]*\.js/, 'img_assist_textarea.js' ));
    break;
  }
}

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

//#321844
if (typeof(initLoader) == 'undefined') {
  var myDoc, myForm, myTextarea, hasInputFormat;

  var initLoader = function() {
    // Save the references to the parent form and textarea to be used later.
    myDoc      = window.opener.document; // global (so don't use var keyword)
    myForm     = '';
    myTextarea = '';
    hasInputFormat = false;

    var args = getArgs(); // get the querystring arguments
    var textarea = args.textarea;

    // Reference the form object for this textarea.
    if (myDoc.getElementsByTagName) {
      var f = myDoc.getElementsByTagName('form');
      for (var i=0; i<f.length; i++) {
        // Is this textarea is using an input format?
        if (f[i]['edit-format']) {
          hasInputFormat = true;
        }
        if (f[i][textarea]) {
          myForm = f[i];
          myTextarea = f[i][textarea];
          break;
        }
      }
    }
    frames['img_assist_main'].window.location.href = BASE_URL + 'index.php?q=img_assist/thumbs/myimages';
  }
}
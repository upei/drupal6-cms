// $Id: fckeditor.config.js,v 1.5.2.5.2.12 2008/12/12 19:37:35 wwalc Exp $

/*
 WARNING: clear browser's cache after you modify this file.
 If you don't do this, you may notice that browser is ignoring all your changes.
*/

/*
 Define as many toolbars as you need, you can change toolbar names
 DrupalBasic will be forced on some smaller textareas (if enabled)
 if you change the name of DrupalBasic, you have to update
 FCKEDITOR_FORCE_SIMPLE_TOOLBAR_NAME in fckeditor.module
 */

//uncomment these three lines to enable teaser break and page break plugins
//remember to add 'DrupalBreak' and 'DrupalPageBreak' buttons to the toolbar
FCKConfig.Plugins.Add( 'drupalbreak', 'en,pl,ru' ) ;
FCKConfig.Plugins.Add( 'imgassist' ) ;
//To enable plugins below you should install additional Drupal modules.
//Please refer to the README.txt for more instructions.
//FCKConfig.Plugins.Add( 'drupalpagebreak', 'en,pl,ru' ) ;
//FCKConfig.Plugins.Add( 'linktonode', 'en,pl' ) ;
//FCKConfig.Plugins.Add( 'linktomenu', 'en,pl' ) ;
/*
 This toolbar is dedicated to users with "Full HTML" access
 some of commands used here (like 'FontName') use inline styles,
 which unfortunately are stripped by "Filtered HTML" filter
 */
FCKConfig.ToolbarSets['DrupalFull'] = [
['Source'],
['Cut','Copy','Paste','PasteText','PasteWord'],
['Undo','Redo','-','Find','Replace','-','SelectAll','RemoveFormat'],
['Bold','Italic','Underline','StrikeThrough','-','Subscript','Superscript'],
['OrderedList','UnorderedList','-','Outdent','Indent','Blockquote'],
['JustifyLeft','JustifyCenter','JustifyRight'],
/* 
 * EXPERIMENTAL
 * Uncomment the line below to enable linktonode and linktomenu buttons
 * ATTENTION: Link to Content module must be installed first!
 * Remember to load appropriate plugins with FCKConfig.Plugins.Add command a couple of lines above
 */
//['Link','Unlink','LinkToNode','LinkToMenu','Anchor'],
['Link','Unlink','Anchor'],
['Image','Flash','Table','Rule','SpecialChar','DrupalBreak'],
//uncomment this line to enable the page break button
//remember to load appropriate plugin with FCKConfig.Plugins.Add
//['Image','Flash','Table','Rule','SpecialChar','DrupalBreak','DrupalPageBreak'],
'/',
['FontFormat','FontName','FontSize'],
['TextColor','BGColor','ShowBlocks']
] ;

FCKConfig.ToolbarSets['DrupalBasic'] = [
['FontFormat','-','Bold','Italic','-','OrderedList','UnorderedList','-','Link','Unlink', 'Image']
] ;

//This toolbar should work fine with "Filtered HTML" filter
FCKConfig.ToolbarSets['DrupalFiltered'] = [
['Source'],
['Cut','Copy','Paste','PasteText','PasteWord'],
['Undo','Redo','-','Find','Replace','-','SelectAll','RemoveFormat'],
/* 
 * EXPERIMENTAL
 * Uncomment the line below to enable linktonode and linktomenu buttons
 * ATTENTION: Link to Content module must be installed first!
 * Remember to load appropriate plugins with FCKConfig.Plugins.Add command a couple of lines above
 */
//['Link','Unlink','LinkToNode','LinkToMenu','Anchor'],
['Link','Unlink','Anchor'],
['Image','Flash','Table','Rule','Smiley','SpecialChar'],
'/',
['FontFormat'],
['Bold','Italic','Underline','StrikeThrough','-','Subscript','Superscript'],
['OrderedList','UnorderedList','-','Outdent','Indent','Blockquote'],
//uncomment this line to the enable page break button
//remember to load appropriate plugin with FCKConfig.Plugins.Add
//['JustifyLeft','JustifyCenter','JustifyRight','DrupalBreak','DrupalPageBreak','ShowBlocks'],
['JustifyLeft','JustifyCenter','JustifyRight','DrupalBreak','ShowBlocks'],
] ;

//helper function to add button at the end of the toolbar
function addToolbarElement(element, toolbar, pos){
  var ts = FCKConfig.ToolbarSets ;
  if (ts[toolbar]) {
    var len=ts[toolbar].length;
    if (pos>=len) pos=len-1;
    if (ts[toolbar][(len -pos -1)] == '/') pos++;
    if (pos>=len) pos=len-1;
    if (!ts[toolbar][(len -pos -1)]) pos++;
    FCKConfig.ToolbarSets[toolbar][(len -pos -1)].push(element);
  }
}

// Protect PHP code tags (<?...?>) so FCKeditor will not break them when
// switching from Source to WYSIWYG.
// Uncommenting this line doesn't mean the user will not be able to type PHP
// code in the source. This kind of prevention must be done in the server side
// (as does Drupal), so just leave this line as is.
FCKConfig.ProtectedSource.Add( /<\?[\s\S]*?\?>/g ) ; // PHP style server side code

var _FileBrowserLanguage = 'php' ;
var _QuickUploadLanguage = 'php' ;

// This overrides the IndentLength/IndentUnit settings.
FCKConfig.IndentClasses = ['rteindent1','rteindent2','rteindent3','rteindent4'] ;

// [ Left, Center, Right, Justified ]
FCKConfig.JustifyClasses = ['rteleft','rtecenter','rteright','rtejustify'] ;
//Set to 'encode' if you want to obfuscate emails with javascript
FCKConfig.EMailProtection = 'none' ;

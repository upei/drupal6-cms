********************************************************************
                     D R U P A L    M O D U L E
********************************************************************
Name: TinyMCE module

Current Maintainers;
              kreynen http://drupal.org/user/48877
              Allie Micka http://drupal.org/user/15091
              m3avrck http://drupal.org/user/12932
              nedjo http://drupal.org/user/4481
              Steve McKenzie http://drupal.org/user/45890
              ufku http://drupal.org/user/9910

Past Maintainers:
              Matt Westgate <drupal AT asitis DOT org> and
              Jeff Robbins <robbins AT jjeff DOT com>
              Richard Bennett <richard.b AT gritechnologies DOT com>

TinyMCE is a platform independent web based Javascript HTML WYSIWYG editor control 
released as Open Source under LGPL by Moxiecode Systems AB. It has the ability to 
convert HTML TEXTAREA fields or other HTML elements to editor instances.

IMPORTANT!!!
  TinyMCE.module requires IMCE.module to enable these feature: File/Image Manager, Quota,
  Auto Resize, folder per user, file upload, file delete, etc.

README:
********************************************************************
Once TinyMCE is enabled, the default behavior is that all textareas
will use TinyMCE for all users. The admin can change these defaults
at

  administer > settings > tinymce

The admin can choose what theme TinyMCE should be the default and
user's can override this by editing their account (if they've been
given permissions to do so). User's also have the option of disabling
TinyMCE completely.

The admin can also define which pages TinyMCE should be used on.
This cannot be changed on a per user basis.


PLUGINS FOR TINYMCE:
********************************************************************
Adding plugins to TinyMCE is very easy. By default, all TinyMCE
plugins are disabled, but can easily be enabled by going to:
   
   Administer > settings > tinymce
   
And then editing a profile (make sure you create one first!) and going
to the Buttons & Plugins section. To enable a button or a plugin,
simply check a box and TinyMCE will automatically be updated. To find
out more info on what a specific button or plugin does, click the 
corresponding link (note not all buttons have help text).

If you wish to add more plugins to TinyMCE, simply extract these
plugins to the folder: tinymce\jscripts\tiny_mce\plugins

Then open up plugin_reg.php, found in the TinyMCE module folder.

Add the following lines:

  $plugins['plugin_name'] = array();
  $plugins['plugin_name']['theme_advanced_buttons3'] = array('icon_name');
     // note, you can choose which row of buttons to use by changing
     // the 3 to either 1 or 2
  $plugins['plugin_name']['plugin_property'] = array('property_value');
  
Be sure to set the 'plugin_name' to the name of the plugin (generally
the plugin folder name) and set the 'icon_name' and other properties
(properties are optional). See plugin_reg.php for more examples.

To add Drupal specific plugins, TinyMCE comes bundled with plugins
in the main module directory. These plugins include:

  - drupalimage: works in conjunction with the img_assist Drupal
    module
    
    NOTE: If you want to use img_assist with TinyMCE, you don't have to
      install a plugin. Just enable the img_assist module and click
      the photo icon that appears below each textarea.

Follow the directions in the README.txt for these plugins to enable them.


CAVEATS
********************************************************************
By default, Drupal uses the 'Filtered HTML' input format for adding
content to the site and this can create conflicts with TinyMCE. It's
best when using this editor to use an input format that has all
filters disabled. What I usually do is create an input format called
'Rich-text editing' and set that as the default format for roles which
use TinyMCE exclusively. To modify your input formats go to:

    Administer > input formats > configure > configure filters


TWEAKING THE TINYMCE THEME
********************************************************************

Developers have complete control over when and how tinymce is enabled
for each textarea inside Drupal by creating a custom Drupal theme
function. The following example assumes you're using a phptemplate based theme.

Put the following function in your themes template.php file:

/**
 * Customize a TinyMCE theme.
 *
 * @param init
 *   An array of settings TinyMCE should invoke a theme. You may override any
 *   of the TinyMCE settings. Details here:
 *
 *    http://tinymce.moxiecode.com/wrapper.php?url=tinymce/docs/using.htm
 *
 * @param textarea_name
 *   The name of the textarea TinyMCE wants to enable.
 *
 * @param theme_name
 *   The default tinymce theme name to be enabled for this textarea. The
 *   sitewide default is 'simple', but the user may also override this.
 *
 * @param is_running
 *   A boolean flag that identifies id TinyMCE is currently running for this
 *   request life cycle. It can be ignored.
 */
function theme_tinymce_theme($init, $textarea_name, $theme_name, $is_running) {
  switch ($textarea_name) {
    // Disable tinymce for these textareas
    case 'log': // book and page log
    case 'img_assist_pages':
    case 'caption': // signature
    case 'pages':
    case 'access_pages': //TinyMCE profile settings.
    case 'user_mail_welcome_body': // user config settings
    case 'user_mail_approval_body': // user config settings
    case 'user_mail_pass_body': // user config settings
    case 'synonyms': // taxonomy terms
    case 'description': // taxonomy terms
      unset($init);
      break;

    // Force the 'simple' theme for some of the smaller textareas.
    case 'signature':
    case 'site_mission':
    case 'site_footer':
    case 'site_offline_message':
    case 'page_help':
    case 'user_registration_help':
    case 'user_picture_guidelines':
      $init['theme'] = 'simple';
      foreach ($init as $k => $v) {
        if (strstr($k, 'theme_advanced_')) unset($init[$k]);
      }
      break;
  }

  /* Example, add some extra features when using the advanced theme.
  
  // If $init is available, we can extend it
  if (isset($init)) {
    switch ($theme_name) {
     case 'advanced':
       $init['extended_valid_elements'] = array('a[href|target|name|title|onclick]');
       break;
    }
  }
  
  */

  // Always return $init
  return $init;
}

If you study the above function you can see that tinymce can be completely
disabled or you can even switch themes for a given textarea.

See the TinyMCE manual for details on the parameters that can be
sent to TinyMCE:

http://tinymce.moxiecode.com/documentation.php


TINYMCE KEYBOARD SHORTCUTS
********************************************************************
Ctrl+Z  Undo
Ctrl+Y  Redo
Ctrl+B  Bold
Ctrl+I  Italic
Ctrl+U  Underline

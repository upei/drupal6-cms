<?php
// $Id: fckeditor.help.inc,v 1.1.2.9 2008/10/09 08:57:52 wwalc Exp $
/**
 * FCKeditor - The text editor for Internet - http://www.fckeditor.net
 * Copyright (C) 2003-2008 Frederico Caldeira Knabben
 *
 * == BEGIN LICENSE ==
 *
 * Licensed under the terms of any of the following licenses at your
 * choice:
 *
 *  - GNU General Public License Version 2 or later (the "GPL")
 *    http://www.gnu.org/licenses/gpl.html
 *
 *  - GNU Lesser General Public License Version 2.1 or later (the "LGPL")
 *    http://www.gnu.org/licenses/lgpl.html
 *
 *  - Mozilla Public License Version 1.1 or later (the "MPL")
 *    http://www.mozilla.org/MPL/MPL-1.1.html
 *
 * == END LICENSE ==
 *
 * @file
 * FCKeditor Module for Drupal 6.x
 *
 * This module allows Drupal to replace textarea fields with FCKeditor.
 *
 * This HTML text editor brings to the web many of the powerful functionalities
 * of known desktop editors like Word. It's really  lightweight and doesn't
 * require any kind of installation on the client computer.
 */

function fckeditor_help_delegate($path, $arg) {
  switch ($path) {
    case 'admin/settings/help#description':
      $output = t('Enables the usage of FCKeditor (WYSIWYG editor) instead of plain text fields.');
      break;

    case 'admin/settings/fckeditor':
      if (!empty($arg[3]) && in_array($arg[3], array("addg", "editg"))) {
        $output = '<p>'. t('The Global Profile allows you to define settings that are common for all profiles. Values defined in other profiles will be appended to the global configuration. This way you can avoid repeating some of the settings that are usually the same in each profile.') .'</p>';
        break;
      }
      else if (!empty($arg[3]) && in_array($arg[3], array("add", "edit"))) {
        $output = '<p>'. t('Note: FCKeditor is highly configurable. The most commonly used features are listed below. If you want to take a look at all available settings, open "!fckconfig" and then customize "!fckeditor_config" to your needs. This is also the only way to define new toolbar sets. It is advised to not edit "fckconfig.js" because you may overwrite it accidentally when you update the editor.', array('!fckconfig' => drupal_get_path('module', 'fckeditor') ."/fckeditor/fckconfig.js", '!fckeditor_config' => drupal_get_path('module', 'fckeditor') ."/fckeditor.config.js")) .'</p>';
        break;
      }
      else if (!empty($arg[3]) && in_array($arg[3], array("delete", "deleteg"))) {
        break;
      }
      $output = '<p>'. t('The FCKeditor module allows Drupal to replace textarea fields with a rich text or <acronym title="What You See Is What You Get">WYSIWYG</acronym> editor. This editor brings many of the powerful functionalities of known desktop editors like Word to the web. It\'s relatively lightweight and doesn\'t require any kind of installation on the client computer.') .'</p><p>'. t('More information about the editor is located at the <a href="!fckeditorlink">FCKeditor homepage</a>. A small user guide is located at <a href="!userguidelink">FCKeditor userguide</a>.', array('!fckeditorlink' => 'http://www.fckeditor.net', '!userguidelink' => 'http://docs.fckeditor.net/FCKeditor/Users_Guide')) .'</p>';
      $output .= '<p>'. t('Profiles can be defined based on user roles. A FCKeditor profile can define which pages receive this FCKeditor capability, what buttons or themes are enabled for the editor, how the editor is displayed, and a few other editor functions. It is possible also to define the Global Profile that will hold values that will be appended to all other profiles.') .'</p><p>'. t('Lastly, only users with the "access fckeditor" <a href="!permission">permission</a> will be able to use FCKeditor.', array('!permission' => url('admin/user/permissions'))) .'</p>';
      break;

    case 'admin/help#fckeditor':
      $output = '<p>'. t('The FCKeditor module allows Drupal to replace textarea fields with a rich text or <acronym title="What You See Is What You Get">WYSIWYG</acronym> editor. This editor brings many of the powerful functionalities of known desktop editors like Word to the web. It\'s relatively lightweight and doesn\'t require any kind of installation on the client computer.') .'</p><p>'. t('More information about the editor is located at the <a href="!fckeditorlink">FCKeditor homepage</a>. A small user guide is located at <a href="!userguidelink">FCKeditor userguide</a>.', array('!fckeditorlink' => 'http://www.fckeditor.net', '!userguidelink' => 'http://docs.fckeditor.net/FCKeditor/Users_Guide')) .'</p>';
      $output .= '<h3>'. t('Configuration') .'</h3>';
      $output .= '<ol>';
      $output .= '<li>'. t('Go to the <a href="!fckeditorlink">FCKeditor homepage</a> and download the latest version of FCKeditor. Then uncompress the contents of the "fckeditor" directory of the downloaded file to %fckeditordir.', array('!fckeditorlink' => 'http://www.fckeditor.net/download', '%fckeditordir' => base_path() . drupal_get_path('module', 'fckeditor') .'/fckeditor/')) .'</li>';
      $output .= '<li>'. t("Enable the module as usual from Drupal's admin pages.") .'</li>';
      $output .= '<li>'. t('Grant permissions for use of FCKeditor in <a href="!path2">Administer > User Management > Permissions</a>. See the "How to enable the built-in file browser" section how to enable the file browser feature.', array('!path2' => url('admin/user/permissions'))) .'</li>';
      $output .= '<li>'. t('Under <a href="!path1">Administer > Site configuration > FCKeditor</a>, adjust the fckeditor profiles. In each profile you can choose which textareas will be replaced by FCKeditor, select default toolbar and configure some more advanced settings.', array('!path1' => url('admin/settings/fckeditor'))) .'</li>';
      $output .= '<li>'. t('For the Rich Text Editing to work you also need to configure your <a href="!filterlink">filters</a> for the users that may access Rich Text Editing. Either grant those users Full HTML access or use the following: <br/><code>!filter</code>.', array('!filterlink' => url('admin/settings/filters'), '!filter' => htmlentities('<a> <p> <span> <div> <h1> <h2> <h3> <h4> <h5> <h6> <img> <map> <area> <hr> <br> <br /> <ul> <ol> <li> <dl> <dt> <dd> <table> <tr> <td> <em> <b> <u> <i> <strong> <font> <del> <ins> <sub> <sup> <quote> <blockquote> <pre> <address> <code> <cite> <embed> <object> <param> <strike> <caption>'))) .'</li>';
      $output .= '<li>'. t('To have a better control over line breaks, you should disable "Line break converter" in the chosen filter (recommended).') .'</li>';
      $output .= '<li>'. t('Modify the fckeditor.config.js file to custom your needs (optional). You may copy the needed configuration lines from the default FCKeditor configuration settings ("!fckconfig"), the lines in fckeditor.config.js will override most settings.', array('!fckconfig' => base_path() . drupal_get_path('module', 'fckeditor') .'/fckeditor/fckconfig.js')) .'</li>';
      $output .= '</ol>';

      $output .= '<a name="fieldinclexcl"></a>';
      $output .= '<h3>'. t('Defining field inclusion/exclusions') .'</h3>';
      $output .= '<p>'. t('In order to specifically display FCKeditor on those text areas on which you need it, the FCKeditor module provides a powerfull method to define fields that should be enhanced with FCKeditor. The first choice you have to make is whether you want to display FCKeditor on all textareas and define a list of exceptions, or if you don\'t want to display FCKeditor unless it is specifically enabled. This choice is made in the "Use inclusion or exclusion mode" setting.') .'</p>';
      $output .= '<p>'. t('Next, the list of exceptions has to be defined. This list follows a specific syntax: the path to a field is defined by specifying the content type followed by "@" character, specifying the path followed by dot and appending the field name at the end. You may decide to not use the content type. The field "edit-log" on page "node/add/page" would thus be addressed as "node/add/page.edit-log". You can use wildcards * and ? anywhere in this line. If you have a dot in your field name and it causes problems, you can escape it with a slash (\).') .'</p>';

      $output .= '<strong>'. t('Some examples:') .'</strong>';
      $output .= '<ul>';
      $output .= '<li>'. t('"node/add/page": matches all fields on "node/add/page".') .'</li>';
      $output .= '<li>'. t('"*.edit-log": matches all fields called edit-log on any page.') .'</li>';
      $output .= '<li>'. t('"blog@*.edit-body": matches all fields of type "blog" called edit-log, on any page.') .'</li>';
      $output .= '<li>'. t('"forum@*.*": matches all fields of type "forum" on any page.') .'</li>';
      $output .= '<li>'. t('"node/add/*": matches all fields on pages such as "node/add/page", "node/add/story", etc.') .'</li>';
      $output .= '<li>'. t('"node/add/*.edit-log": matches all edit-log fields on pages such as "node/add/page", "node/add/story", etc.') .'</li>';
      $output .= '<li>'. t('"node/add/*.edit-user-*": matches fields starting with "edit-user-" on pages starting with "node/add/"') .'</li>';
      $output .= '</ul>';

      $output .= '<h3>'. t('Troubleshooting') .'</h3>';
      $output .= '<p>';
      $output .= t('Take a look at <a href="!list">list of common problems</a> when installing FCKeditor.', array('!list' => 'http://drupal.fckeditor.net/troubleshooting'));
      $output .= ' '. t('If you are looking for more information, have any troubles in configuration or if you found an issue, please visit the <a href="!official">official project page</a>.', array('!official' => 'http://drupal.org/project/fckeditor'));
      $output .= ' '. t('More information about how to tune up FCKeditor for your theme can be found <a href="!tricks">here</a>.', array('!tricks' => 'http://drupal.fckeditor.net/tricks'));
      $output .= '</p>';

      $output .= '<h3>'. t('Plugins: Teaser break and Pagebreak') .'</h3>';
      $output .= '<p>'. t('By default, FCKeditor module comes with two plugins that can handle teaser break (&lt;!--break--&gt;) and pagebreak (&lt;!--pagebreak--&gt;). You can enable any (or even both) of them.') .'</p>';
      $output .= '<ol>';
      $output .= '<li>'. t('Open "!fckeditor.config.js" and uncomment these three lines: <pre>!code</pre>', array('!fckeditor.config.js' => base_path() . drupal_get_path('module', 'fckeditor') .'/fckeditor.config.js', '!code' => "\nFCKConfig.PluginsPath = '../../plugins/';\nFCKConfig.Plugins.Add('drupalbreak');\nFCKConfig.Plugins.Add('drupalpagebreak');\n")) .'</li>';
      $output .= '<li>'. t('The second step is to add buttons to the toolbar (in the same file). The button names are: "DrupalBreak", "DrupalPageBreak". For example if you have a toolbar with an array of buttons defined as follows: <pre>!buttons1</pre> simply add those two buttons at the end of array (remember about single quotes): <pre>!buttons2</pre>', array('!buttons1' => "['Image','Flash','Table','Rule','SpecialChar']", '!buttons2' => "['Image','Flash','Table','Rule','SpecialChar', 'DrupalBreak', 'DrupalPageBreak']")) .'</li>';
      $output .= '</ol>';

      $output .= '<h3>'. t('Uploading images and files') .'</h3>';
      $output .= '<p>'. t('There are three ways for uploading files:') .'</p>';
      $output .= '<ol>';
      $output .= '<li>'. t('By using the built-in file browser.') .'</li>';
      $output .= '<li>'. t('By using a module like <a href="!imce">IMCE</a>.', array('!imce' => 'http://drupal.org/project/imce')) .'</li>';
      $output .= '<li>'. t('By using the core upload module.') .'</li>';
      $output .= '</ol>';

      // The rest is untranslated for the moment.
      $output .= '<h3>'. t('How to enable the built-in file browser') .'</h3>';
      $output .= '<p>'. t('The editor gives the end user the flexibility to create a custom file browser that can be integrated on it. The included file browser allows users to view the content of a specific directory on the server and add new content to that directory (create folders and upload files).') .'</p>';
      $output .= '<ol>';
      $output .= '<li>';
      $output .= ' '. t('To enable file browsing you need to edit the connector configuration file in your fckeditor module directory, the file should be in %config.', array('%config' => base_path() . drupal_get_path('module', 'fckeditor') ."/fckeditor/editor/filemanager/connectors/php/config.php"));
      $output .= ' '. t('In this file you will need to enable the file browser by adding one line that includes a file with the special authentication function for Drupal ("filemanager.config.php").') .'<br />'. t('Add this code:<br /><pre>!code1</pre> straight below this line: <pre>!code2</pre> The config.php file also holds some other important settings, please take a look at it and adjust it to your needs (optional).', array('!code1' => '  require_once \'../../../../../filemanager.config.php\';', '!code2' => "  \$Config['UserFilesAbsolutePath'] = '' ;"));
      $output .= '</li>';
      $output .= '<li>'. t('Locate file named "settings.php" inside your drupal directory (usually "sites/default/settings.php") and set <strong>$cookie_domain</strong> variable to the appropiate domain (remember to uncomment that line). If you not do this, FCKeditor will claim that file browser is disabled.') .'</li>';
      $output .= '<li>'. t('Enabling file uploads is <strong>a security risk</strong>. That\'s why you have to grant a <a href="!link">separate permission</a> to enable the file browser to certain groups (assign the "allow fckeditor file uploads" permissions).', array('!link' => url('admin/user/permissions'))) .'</li>';
      $output .= '<li>'. t('Lastly, adjust the "File browser settings" for each <a href="!profile">profile</a>: set "File browser type" to "Built-in filebrowser".', array('!profile' => url('admin/settings/fckeditor'))) .'</li>';
      $output .= '</ol>';

      $output .= '<h3>'. t('Modules: Image Assist') .'</h3>';
      $output .= '<p>'. t('Image Assist can be integrated with FCKeditor. To do this, simply copy the "!iaf1" file to "!iaf2".', array('!iaf1' => drupal_get_path('module', 'fckeditor') .'/img_assist_fckeditor.js', '!iaf2' => drupal_get_path('module', 'img_assist') .'/img_assist_fckeditor.js')) .'</p>';

      break;
  }
  return !empty($output) ? $output : '';
}
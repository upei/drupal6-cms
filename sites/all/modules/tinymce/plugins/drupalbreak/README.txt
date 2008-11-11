Introduction
------------

This tinyMCE plugin is designed to be used in conjunction with the Drupal CMS
More details available at http://drupal.org.

This plugin adds two buttons to the tinyMCE toolbar. One button inserts a visible
<!--break--> tag into the editor. This effectively splits the teaser and body of a story
in Drupal 4.6 or higher. The other button inserts a <!--pagebreak--> tag. This is
made to be used with the paging module <http://drupal.org/project/paging>.

Installation
------------
1. Copy the drupalbreak directory to the plugins directory of TinyMCE (/jscripts/tiny_mce/plugins).
2. Open up plugin_reg.php and add the following lines to end of that file:
  
    $plugins['drupalbreak'] = array();
    $plugins['drupalbreak']['theme_advanced_buttons3'] = array('drupalbreak', 'drupalpagebreak');
      
3. Then enable this plugin under Admin > Settings > TinyMCE, under the Buttons & Plugins section
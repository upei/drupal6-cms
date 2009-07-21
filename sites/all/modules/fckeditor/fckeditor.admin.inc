<?php
// $Id: fckeditor.admin.inc,v 1.1.2.34 2009/03/11 14:22:14 wwalc Exp $
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

/**
 * Main administrative page
 */
function fckeditor_admin_main() {
  $editor_path = fckeditor_path(TRUE);
  $fckconfig_file = $editor_path .'/fckconfig.js';
  if (!file_exists($fckconfig_file)) {
    drupal_set_message(t('Checking for %filename.', array('%filename' => $fckconfig_file)));
    drupal_set_message(t('The FCKeditor component is not installed correctly. Please go to the <a href="!fckeditorlink">FCKeditor homepage</a> to download the latest version. After that you must extract the files to %fckeditorpath and make sure that the directory %fckeditorsubdir and the file %fckeditorfile exist. Refer to the <a href="!readme">readme.txt</a> for more information.', array('!fckeditorlink' => url('http://www.fckeditor.net/download'), '!readme' => url('admin/help/fckeditor'), '%fckeditorpath' => $editor_path .'/fckeditor/', '%fckeditorsubdir' => $editor_path .'/editor', '%fckeditorfile' => $editor_path .'/fckeditor.js')), 'error');
    drupal_set_message(t('If you have FCKeditor already installed please edit <a href="!editg">FCKeditor Global Profile</a> and update FCKeditor path.', array('!editg' => url('admin/settings/fckeditor/editg'))), 'warning');
    return FALSE;
  }

  $access_fckeditor_roles = user_roles(FALSE, 'access fckeditor');
  if (!$access_fckeditor_roles) {
    drupal_set_message(t('There is currently no role with the "access fckeditor" permission. Visit <a href="!acl">permissions</a> administration section.', array('!acl' => url('admin/user/permissions'))), 'warning');
  }
  else {
    $result = db_query_range("SELECT name FROM {fckeditor_settings} WHERE name<>'FCKeditor Global Profile'", 0, 1);
    $has_profiles = FALSE;
    //find profile other than Global
    if (($obj = db_fetch_object($result))) {
      $has_profiles = TRUE;
    }

    //find roles with profiles
    $result = db_query("SELECT rid FROM {fckeditor_role}");
    $rids = array();
    while (($obj = db_fetch_object($result))) {
        $rids[] = $obj->rid;
    }
    $rids = array_unique($rids);
    if (!$has_profiles) {
      drupal_set_message(t('No FCKeditor profiles found. At this moment, nobody is able to use FCKeditor. Create new profile below.'), 'error');
    }
    else {
      //not all roles with access fckeditor has their FCKeditor profile assigned
      $diff = array_diff(array_keys($access_fckeditor_roles), $rids);
      if ($diff) {
        $list = "<ul>";
        foreach ($diff as $rid) {
          $list .= "<li>". $access_fckeditor_roles[$rid] ."</li>";
        }
        $list .= "</ul>";
        drupal_set_message(t('Not all roles with <a href="!access">access fckeditor</a> permission are associated with FCKeditor profiles. As a result, users having the following roles may be unable to use FCKeditor: !list Create new or edit FCKeditor profiles below and in the <em>Basic setup</em> section, check "Roles allowed to use this profile".', array('!access' => url('admin/user/permissions'), '!list' => $list)), 'warning');
      }
    }
  }

  return fckeditor_profile_overview();
}

/**
 * Controller for fckeditor profiles.
 */
function fckeditor_profile_overview() {
  $output = '';

  $profiles = fckeditor_profile_load();
  if ($profiles) {
    $access_fckeditor_roles = user_roles(FALSE, 'access fckeditor');
    $header = array(t('Profile'), t('Roles'), t('Operations'));
    foreach ($profiles as $p) {
      $rids = $p->rids;
      if ($p->name !== "FCKeditor Global Profile") {
        foreach (array_keys($p->rids) as $rid) {
          if (!isset($access_fckeditor_roles[$rid])) {
            unset($rids[$rid]);
          }
        }
        $rows[] = array(
          array('data' => $p->name, 'valign' => 'top'),
          array('data' => implode("<br />\n", $rids)),
          array('data' =>
            l(t('edit'), 'admin/settings/fckeditor/edit/'. urlencode($p->name)) .' '.
            l(t('clone'), 'admin/settings/fckeditor/clone/'. urlencode($p->name)) .' '.
            l(t('delete'), 'admin/settings/fckeditor/delete/'. urlencode($p->name)), 'valign' => 'top'
          )
        );
      }
    }
    $output .= '<h3>'. t('Profiles') .'</h3>';
    $output .= theme('table', $header, $rows);
    $output .= '<p>'. l(t('Create new profile'), 'admin/settings/fckeditor/add') .'</p>';
  }
  else {
    drupal_set_message(t('No profiles found. Click here to <a href="!create">create a new profile</a>.', array('!create' => url('admin/settings/fckeditor/add'))));
  }

  $rows = array();
  if (!isset($profiles['FCKeditor Global Profile'])) {
    drupal_set_message(t('Global profile not found. Click here to <a href="!create">create the global profile</a>.', array('!create' => url('admin/settings/fckeditor/addg'))));
  }
  else {
    $output .= "<h3>". t("Global settings") ."</h3>";
    $rows[] = array(
      array('data' => t('FCKeditor Global Profile'), 'valign' => 'top'),
      array('data' => l(t('edit'), 'admin/settings/fckeditor/editg') ." ". l(t('delete'), 'admin/settings/fckeditor/delete/FCKeditor Global Profile'), 'valign' => 'top')
    );
    $output .= theme('table', array(t('Profile'), t('Operations')), $rows);
  }
  return $output;
}

/**
 * Clone profile
 */
function fckeditor_admin_profile_clone_form($form_state, $oldprofile) {
  return fckeditor_admin_profile_form($form_state, $oldprofile);
}

function fckeditor_admin_profile_clone_form_validate($form_state, $oldprofile) {
  fckeditor_admin_profile_form_validate($form_state, $oldprofile);
}

function fckeditor_admin_profile_clone_form_submit($form, &$form_state) {
  $edit =& $form_state['values'];
  drupal_set_message(t('Your FCKeditor profile has been created.'));
  $settings = fckeditor_admin_values_to_settings($edit);
  db_query("INSERT INTO {fckeditor_settings} (name, settings) VALUES ('%s', '%s')", $edit['name'], $settings);
  fckeditor_rebuild_selectors($edit['name']);
  if (!empty($edit['rids'])) {
    foreach (array_keys($edit['rids']) as $rid) {
      if ($edit['rids'][$rid]!=0) {
        db_query("INSERT INTO {fckeditor_role} (name, rid) VALUES ('%s', %d)", $edit['name'], $rid);
      }
    }
  }
  $form_state['redirect'] = 'admin/settings/fckeditor';
}

/**
 * Form builder for a normal profile
 */
function fckeditor_admin_profile_form($form_state, $profile = NULL) {
  if ($profile != NULL) {
    $form['_profile'] = array(
      '#type' => 'value',
      '#value' => $profile,
    );
  }
  else {
    $profile = new stdClass();
  }

  module_load_include('lib.inc', 'fckeditor');

  $toolbar_options = fckeditor_load_toolbar_options();
  $skin_options = fckeditor_load_skin_options();
  $lang_options = fckeditor_load_lang_options();

  // Only display the roles that currently don't have a fckeditor profile. One
  // profile per role.
  $orig_roles = user_roles(FALSE, 'access fckeditor');
  $roles = $orig_roles;

  if (!empty($profile->rids) && !user_roles(FALSE, 'access fckeditor')) {
    drupal_set_message(t('You haven\'t assigned "access fckeditor" <a href="!permissions">permissions</a> yet. It is recommended to assign the "access fckeditor" <a href="!permissions">permissions</a> before updating FCKeditor profiles.', array('!permissions' => url('admin/user/permissions'))), 'warning');
  }

  if (empty($profile->name)) {
    $result = db_query("SELECT DISTINCT(rid) FROM {fckeditor_role}");
    while (($data = db_fetch_object($result))) {
      if ((empty($profile->rids) || !in_array($data->rid, array_keys((array) $profile->rids))) && !form_get_errors()) {
        unset($roles[$data->rid]);
      }
    }
    if (count($orig_roles) != count($roles)) {
      drupal_set_message(t('Not all user roles are shown since they already have fckeditor profiles. You must first unassign profiles in order to add them to a new one.'));
    }
  }

  $form['basic'] = array(
    '#type' => 'fieldset',
    '#title' => t('Basic setup'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE
  );

  if (arg(3) == 'clone') {
    //load all profiles to check their names
    $profiles = fckeditor_profile_load();
    $oldname = $profile->name;
    $maxsize=128;   //default max name length

    $res=array();
    $pat = "/^(?<name>.*?)_(?<n>[0-9]*)$/";
    if (preg_match_all($pat, $oldname, $res)) {     // oldname like 'name_nr'
      $name=$res['name'][0];
      $num=$res['n'][0]+1;
    }
    else{
      $name=$oldname;
      $num=2;
    }

    $newname=substr($name, 0, $maxsize-3) .'_'. $num;   // +limit
    while (isset($profiles[$newname])) {            //find next free number
      $num++;
      $newname=substr($name, 0, $maxsize-3) .'_'. $num;

    }
    //dont clone rids
    $profile->settings['rids']=array();
    $profile->rids=array();
  }
  else {
    $newname = $profile->name;
  }

  $form['basic']['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Profile name'),
    '#default_value' => !empty($profile->name) ? $newname : '',
    '#size' => 40,
    '#maxlength' => 128,
    '#description' => t('Enter a name for this profile. This name is only visible within the fckeditor administration page.'),
    '#required' => TRUE
  );

  $form['basic']['rids'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Roles allowed to use this profile'),
    '#default_value' => !empty($profile->rids) ? array_keys((array) $profile->rids) : array(),
    '#options' => $roles,
    '#description' =>  t('Only roles with "access fckeditor" permission will be shown here. If no role is available, make sure that you have assigned the "access fckeditor" <a href="!permission">permission</a>.', array('!permission' => url('admin/user/permissions'))),
    '#required' => TRUE
  );

  $form['basic']['allow_user_conf'] = array(
    '#type' => 'radios',
    '#title' => t('Allow users to customize FCKeditor appearance'),
    '#default_value' => !empty($profile->settings['allow_user_conf']) ? $profile->settings['allow_user_conf'] : 'f',
    '#options' => array(
      'f' => t('No'),
      't' => t('Yes')
    ),
    '#description' => t('If allowed, users will be able to override the "Editor appearance" by visiting their profile page.'),
  );

  $form['security'] = array(
    '#type' => 'fieldset',
    '#title' => t('Security'),
    '#description' => '<p>'. t("When Drupal saves user data input through a textarea, it's saved in the database in unmodified form. That's why all untrusted textarea input should be run through an input format filter before outputting it to the screen.") .'</p>'.'<p>'. t("Drupal will not, however, filter data for content editor's editing a textarea. Normally, there is no security risk because the unmodified code is displayed as text and will not be rendered as HTML. But with FCKeditor installed, this is not the case, and content editor's are subject to having raw, untrusted code running inside their browsers.") .'</p>'.'<p>'. t("To address this issue, you should select a security filters below to prevent FCKeditor from rendering malicious code. Note that if a textarea's input format is set to \"Full HTML\" (or if the input format of the node doesn't include the filter), FCKeditor will properly ignore the setting below and will not run the code through the security filter.") .'</p>'.'<p>'. t("If any textareas on your site are accessible to unwanted users, we recommend checking the \"HTML Filter\". You may have other modules installed that provide other kinds of security filters and you may use those as long as you trust them to properly filter out malicious code. Note that not all the filters below are security filters and will provide no protection.") .'</p>',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE
  );

  $all = filter_list_all();

  $form['security']['filters'] = array(
    '#type' => 'fieldset',
    '#title' => t('Security filters'),
    '#description' => t('Please choose carefully all filters that protect your content (probably not all filters listed below are security filters).'),
    '#tree' => TRUE,
  );

  //don't bother administrator with filters that definitely are not security filters
  $modules_with_filters_to_skip = array('amazon_filter', 'asy', 'bbcode', 'biblio', 'blockquote', 'bookpost', 'chessboard', 'citation_filter', 'codefilter', 'collapse_text', 'contextlinks', 'coolfilter', 'dialectic', 'dript', 'dme', 'drutex', 'embedfilter', 'ext_link_page', 'extlink', 'elf', 'flickr', 'flickrstickr', 'footnotes', 'formdefaults', 'freelinking', 'gallery', 'geogebra', 'geshifilter', 'gotwo', 'googtube', 'gotcha', 'gtspam', 'hidden_content', 'img_assist', 'image_filter', 'inlinetags', 'insert_view', 'insertframe', 'insertnode', 'interwiki', 'jlightbox', 'jsmath', 'language_sections', 'link_node', 'lootz', 'markdown', 'marksmarty', 'mobile_codes', 'mykml', 'nofollowlist', 'oagwt', 'paging', 'pathfilter', 'pearwiki_filter', 'php', 'pirate', 'reptag', 'scrippet', 'scripturefilter', 'signwriter', 'slideshowpro', 'smartlinebreakconverter', 'smartypants', 'smileys', 'spamspan', 'spam_tokens', 'spoiler', 'table_altrow', 'tablemanager', 'tableofcontents', 'textile', 'tooltips', 'twikifilter', 'typogrify', 'unwrap', 'urlclass', 'urlicon', 'url_replace_filter', 'username_highlighter', 'video_filter', 'quote');

  if (!isset($profile->settings['ss'])) {
    $profile->settings['filters']['filter/0'] = 1;
  }

  foreach ($all as $id => $filter) {
    if (in_array(strtolower($filter->module), $modules_with_filters_to_skip)) {
      continue;
    }
    //skip line break converter and email -> link
    if ($filter->module == 'filter' && in_array($filter->delta, array(1, 2))) {
      continue;
    }
    $form['security']['filters'][$id] = array(
      '#type' => 'checkbox',
      '#title' => $filter->name,
      '#default_value' => !empty($profile->settings['filters'][$id]),
      '#description' => module_invoke($filter->module, 'filter', 'description', $filter->delta),
    );
  }

  $form['security']['ss'] = array(
    '#type' => 'radios',
    '#title' => t('Security settings'),
    '#default_value' => isset($profile->settings['ss']) ? $profile->settings['ss'] : '2',
    '#options' => array(
      '2' => t('Always run security filters for FCKeditor.'),
      '1' => t('Run security filters only when FCKeditor is set to start automatically.'),
    ),
    '#description' => t('There are two ways of starting FCKeditor: automatically and manually (via toggle or in a popup). If you decide to apply security filters only when FCKeditor starts automatically, you\'ll not be protected when toggling manually from plain textarea to FCKeditor or when using FCKeditor in a popup mode. So choose this option only, if you can detect various attacks (mainly XSS) by yourself just by looking at the HTML code.'),
  );

  $form['fckeditor_exclude_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Visibility settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['fckeditor_exclude_settings']['min_rows'] = array(
    '#type' => 'textfield',
    '#title' => t('Minimum rows'),
    '#default_value' => !empty($profile->settings['min_rows']) ? $profile->settings['min_rows'] : '5',
    '#description' => t("FCKeditor will be triggered if the textarea has more rows than entered here. Enter '1' if you do not want to use this feature."),
  );

  $form['fckeditor_exclude_settings']['excl_mode'] = array(
    '#type' => 'radios',
    '#title' => t('Use inclusion or exclusion mode'),
    '#default_value' => (empty($profile->settings['excl_mode']) || in_array($profile->settings['excl_mode'], array(0, 2))) ? 0 : 1,
    '#options' => array(
      '0' => t('Exclude'),
      '1' => t('Include')
    ),
    '#description' => t('Choose the way of disabling/enabling FCKeditor on selected fields/paths (see below). Use exclude to disable FCKeditor on selected fields/paths. Use include if you want to load FCKeditor only on selected paths/fields.'),
  );

  /**
   * get excluded fields - so we can have normal textareas too
   * split the phrase by any number of commas or space characters,
   * which include " ", \r, \t, \n and \f
   */
  $form['fckeditor_exclude_settings']['excl'] = array(
    '#type' => 'textarea',
    '#title' => t('Fields to exclude/include'),
    '#cols' => 60,
    '#rows' => 5,
    '#prefix' => '<div style="margin-left:20px">',
    '#suffix' => '</div>',
    '#default_value' => !empty($profile->settings['excl']) ? $profile->settings['excl'] : '',
    '#description' => t('Enter the paths to the textarea fields on which you want to enable or disable FCKeditor.') .' '. t('Please see the <a href="!helppagelink">help page</a> for more information about defining field names. Short instruction is available below.', array('!helppagelink' => url('admin/help/fckeditor', array('fragment' => 'fieldinclexcl')))) .' <ul><li>'. t('Path structure: <strong>content_type@path.element_id</strong>') .'</li><li>'. t('The following wildcards are available: "*", "?".') .'</li><li>'. t('Content type is optional. You may even specify only path or field id.') .'</li><li>'. t('Examples:') .'<ul><li><em>blog@*.edit-body</em> - '. t('matches all fields of type "blog" called edit-body, on any page.') .'<li><em>node/add/*.edit-user-*</em> - '. t('matches fields starting with "edit-user-" on pages starting with "node/add/') .'</li></ul></li></ul>',
    '#wysiwyg' => FALSE,
  );

  $form['fckeditor_exclude_settings']['simple_incl'] = array(
    '#type' => 'textarea',
    '#title' => t('Force simplified toolbar on the following fields'),
    '#cols' => 60,
    '#rows' => 5,
    '#default_value' => !empty($profile->settings['simple_incl']) ? $profile->settings['simple_incl'] : '',
    '#description' => t('Enter the paths to the textarea fields on which you want to force the simplified toolbar (!name).', array('!name' => FCKEDITOR_FORCE_SIMPLE_TOOLBAR_NAME)) .' '. t('Please see the <a href="!helppagelink">help page</a> for more information about defining field names. Take a look at the exclusion settings (above) for short instruction.', array('!helppagelink' => url('admin/help/fckeditor', array('fragment' => 'fieldinclexcl')))),
    '#wysiwyg' => FALSE,
  );

  $form['appearance'] = array(
    '#type' => 'fieldset',
    '#title' => t('Editor appearance'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['appearance']['default'] = array(
    '#type' => 'radios',
    '#title' => t('Default state'),
    '#default_value' => !empty($profile->settings['default']) ? $profile->settings['default'] : 't',
    '#options' => array(
      't' => t('Enabled'),
      'f' => t('Disabled')
    ),
    '#description' => t('Default editor state. If disabled, rich text editor may still be enabled using toggle or popup window.'),
  );

  $form['appearance']['show_toggle'] = array(
    '#type' => 'radios',
    '#title' => t('Show disable/enable rich text editor toggle'),
    '#default_value' => !empty($profile->settings['show_toggle']) ? $profile->settings['show_toggle'] : 't',
    '#options' => array(
      't' => t('Show'),
      'f' => t('Hide')
    ),
    '#description' => t('Whether or not to show the disable/enable rich text editor toggle below the textarea. Works only if FCKeditor is not running in a popup window (see below).'),
  );

  $form['appearance']['popup'] = array(
    '#type' => 'radios',
    '#title' => t('Use FCKeditor in a popup window'),
    '#default_value' => !empty($profile->settings['popup']) ? $profile->settings['popup'] : 'f',
    '#options' => array(
      'f' => t('No'),
      't' => t('Yes')
    ),
    '#description' => t('If this option is enabled a link to a popup window will be used instead of a textarea replace.'),
  );

  $form['appearance']['skin'] = array(
    '#type' => 'select',
    '#title' => t('Skin'),
    '#default_value' => !empty($profile->settings['skin']) ? $profile->settings['skin'] : 'default',
    '#options' => $skin_options,
    '#description' => t('Choose a default skin.'),
  );

  $form['appearance']['toolbar'] = array(
    '#type' => 'select',
    '#title' => t('Toolbar'),
    '#default_value' => !empty($profile->settings['toolbar']) ? $profile->settings['toolbar'] : 'default',
    '#options' => $toolbar_options,
    '#description' => t('Choose a default toolbar set. To define new toolbar, edit "fckeditor.config.js" located in "!module_path".', array('!module_path' => drupal_get_path('module', 'fckeditor'))),
  );

  $form['appearance']['expand'] = array(
    '#type' => 'radios',
    '#title' => t('Start the toolbar expanded'),
    '#default_value' => !empty($profile->settings['expand']) ? $profile->settings['expand'] : 't',
    '#options' => array(
      't' => t('Expanded'),
      'f' => t('Collapsed')
    ),
    '#description' => t('The toolbar start expanded or collapsed.'),
  );

  $form['appearance']['width'] = array(
    '#type' => 'textfield',
    '#title' => t('Width'),
    '#default_value' => !empty($profile->settings['width']) ? $profile->settings['width'] : '100%',
    '#description' => t("Width in pixels or percent. Example: 400 or 100%."),
    '#size' => 40,
    '#maxlength' => 128,
  );

  $form['appearance']['lang'] = array(
    '#type' => 'select',
    '#title' => t('Language'),
    '#default_value' => !empty($profile->settings['lang']) ? $profile->settings['lang'] : 'en',
    '#options' => $lang_options,
    '#description' => t('The language for the FCKeditor interface.')
  );

  $form['appearance']['auto_lang'] = array(
    '#type' => 'radios',
    '#title' => t('Auto-detect language'),
    '#default_value' => !empty($profile->settings['auto_lang']) ? $profile->settings['auto_lang'] : 't',
    '#options' => array(
      't' => t('Enabled'),
      'f' => t('Disabled')
    ),
    '#description' => t('Use auto detect user language feature.')
  );

  /*
  $form['appearance']['appearance_conf'] = array(
    '#type' => 'select',
    '#title' => t('Ignore this section, use default settings defined in config files'),
    '#default_value' => $profile->settings['appearance_conf'] ? $profile->settings['appearance_conf'] : 'f',
    '#options' => array(
      'f' => t('false'),
      't' => t('true')
    ),
    '#description' => t('Although it is less handy, defining settings only in config files (<code>fckconfig.js</code> and <code>fckeditor.config.js</code>) will slightly leverage your traffic and improve load time of your site. <br/>Warning: if set to true, all changes made in <code>Editor appearance</code> will have no affect on FCKeditor\'s behaviour.'),
  );
  */

  $form['output'] = array(
    '#type' => 'fieldset',
    '#title' => t('Cleanup and output'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['output']['enter_mode'] = array(
    '#type' => 'select',
    '#title' => t('Enter mode'),
    '#default_value' => !empty($profile->settings['enter_mode']) ? $profile->settings['enter_mode'] : 'p',
    '#options' => array(
      'p' => '<p>',
      'br' => '<br>',
      'div' => '<div>'
    ),
    '#description' => t('Set which tag FCKeditor should use when [Enter] key is pressed.')
  );

  $form['output']['shift_enter_mode'] = array(
    '#type' => 'select',
    '#title' => t('Shift + Enter mode'),
    '#default_value' => !empty($profile->settings['shift_enter_mode']) ? $profile->settings['shift_enter_mode'] : 'br',
    '#options' => array(
      'p' => '<p>',
      'br' => '<br>',
      'div' => '<div>'
    ),
    '#description' => t('Set which tag FCKeditor should use when [Shift] + [Enter] is pressed.')
  );

  $form['output']['font_format'] = array(
    '#type' => 'textfield',
    '#title' => t('Font formats'),
    '#default_value' => !empty($profile->settings['font_format']) ? $profile->settings['font_format'] : 'p;div;pre;address;h1;h2;h3;h4;h5;h6',
    '#size' => 40,
    '#maxlength' => 250,
    '#description' => t('Semicolon separated list of HTML font formats. Allowed values are: p;div;pre;address;h1;h2;h3;h4;h5;h6'),
  );

  $form['output']['format_source'] = array(
    '#type' => 'radios',
    '#title' => t('Apply source formatting'),
    '#default_value' => !empty($profile->settings['format_source']) ? $profile->settings['format_source'] : 't',
    '#options' => array(
      't' => t('Yes'),
      'f' => t('No')
    ),
    '#description' => t('When set to "true" the editor will format the XHTML when switching from WYSIWYG view to Source view, by inserting line breaks on some tags endings and indenting paragraphs, tables and lists.'),
  );

  $form['output']['format_output'] = array(
    '#type' => 'radios',
    '#title' => t('Format output'),
    '#default_value' => !empty($profile->settings['format_output']) ? $profile->settings['format_output'] : 't',
    '#options' => array(
      't' => t('Yes'),
      'f' => t('No')
    ),
    '#description' => t('When set to "true" the editor will format the XHTML output by inserting line breaks on some tags endings and indenting paragraphs, tables and lists.'),
  );

  /*
  $form['output']['output_conf'] = array(
    '#type' => 'select',
    '#title' => t('Ignore this section, use default settings defined in config files'),
    '#default_value' => $profile->settings['output_conf'] ? $profile->settings['output_conf'] : 'f',
    '#options' => array(
      'f' => t('False'),
      't' => t('True')
    ),
    '#description' => t('Although it is less handy, defining settings only in config files ("fckconfig.js" and "fckeditor.config.js") will slightly leverage your traffic and improve load time of your site. <br/>Warning: if set to true, all changes made in "Cleanup and output" will have no affect on FCKeditor\'s behaviour.'),
  );
  */

  $form['css'] = array(
    '#type' => 'fieldset',
    '#title' => t('CSS'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE
  );

  $form['css']['css_mode'] = array(
    '#type' => 'select',
    '#title' => t('Editor CSS'),
    '#default_value' => !empty($profile->settings['css_mode']) ? $profile->settings['css_mode'] : 'theme',
    '#options' => array(
      'theme' => t('Use theme css'),
      'self' => t('Define css'),
      'none' => t('FCKeditor default')
    ),
    '#description' => t('Defines the CSS to be used in the editor area.<br />Use theme css - load style.css from current site theme.<br/>Define css - enter path for css file below.<br />FCKeditor default - uses default CSS from editor.')
  );

  $form['css']['css_path'] = array(
    '#type' => 'textfield',
    '#title' => t('CSS path'),
    '#default_value' => !empty($profile->settings['css_path']) ? $profile->settings['css_path'] : "",
    '#size' => 40,
    '#maxlength' => 255,
    '#description' => t('Enter path to CSS file (Example: "css/editor.css") or a list of css files seperated by a comma (Example: "/themes/garland/style.css,http://example.com/style.css"). Make sure to select "Define css" above.<br />Available placeholders:<br /><strong>%h</strong> - host name (!host).<br /><strong>%t</strong> - path to theme (!theme).', array('!host' => base_path(), '!theme' => base_path() . path_to_theme() .'/'))
  );

  $form['css']['css_style'] = array(
    '#type' => 'select',
    '#title' => t('Predefined styles'),
    '#default_value' => !empty($profile->settings['css_style']) ? $profile->settings['css_style'] : 'theme',
    '#options' => array(
      'theme' => t('Use theme fckstyles.xml'),
      'self' => t('Define path to fckstyles.xml'),
      'default' => t('FCKeditor default')
    ),
    '#description' => t('Define the location of "fckstyles.xml" file. It is used by the "Style" dropdown list available in the default toolbar. Copy "!fckstyles.xml" inside your theme directory ("!theme") and adjust it to your needs.', array('!fckstyles.xml' => fckeditor_path(TRUE) .'/fckstyles.xml', '!theme' => path_to_theme() .'/fckstyles.xml'))
  );

  $form['css']['styles_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Predefined styles path'),
    '#default_value' => !empty($profile->settings['styles_path']) ? $profile->settings['styles_path'] : "",
    '#size' => 40,
    '#maxlength' => 255,
    '#description' => t('Enter path to XML file with predefined styles (Example: "/fckstyles.xml"). Be sure to select "define path to fckstyles.xml" above.<br />Available placeholders:<br /><strong>%h</strong> - host name (!host).<br /><strong>%t</strong> - path to theme (!theme).<br /><strong>%m</strong> - path to FCKeditor module (!module).', array('!host' => base_path(), '!theme' => base_path() . path_to_theme() .'/', '!module' => drupal_get_path('module', 'fckeditor')))
  );

  $form['fckeditor_upload_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('File browser settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => t('Set file browser settings. A file browser will allow you to explore the files contained on the server and embed them as links, images or flash movies. Besides the built-in FCKeditor file browser, you can also use a contributed module like <a href="!imce">IMCE</a>, <a href="!ib">Image Browser</a> or <a href="!webfm">Web File Manager</a>. The quick upload setting controls whether images, flash movies and files can be uploaded using the upload tab of the respective dialogs. Please note that these options require manual configuration, check <a href="!readme">readme.txt</a> for more information.', array('!imce' => url('http://drupal.org/project/imce'), '!ib' => url('http://drupal.org/project/imagebrowser'), '!webfm' => url('http://drupal.org/project/webfm'), '!readme' => url('admin/help/fckeditor')))
  );

  $filebrowsers = array(
    'none' => t('None'),
    'builtin' => t('Built-in filebrowser'),
  );

  if (module_exists('imce')) {
    $filebrowsers['imce'] = t('IMCE');
  }

  if (module_exists('imagebrowser')) {
    $filebrowsers['ib'] = t('Image Browser');
  }

  if (module_exists('webfm_popup')) {
    $filebrowsers['webfm'] = t('Web File Manager');
  }

  $form['fckeditor_upload_settings']['filebrowser'] = array(
    '#type' => 'select',
    '#title' => t('File browser type'),
    '#default_value' => !empty($profile->settings['filebrowser']) ? $profile->settings['filebrowser'] : 'none',
    '#options' => $filebrowsers,
    '#description' => t('Select the file browser that you would like to use to upload files, images and flash movies.'),
  );

  $form['fckeditor_upload_settings']['quickupload'] = array(
    '#type' => 'radios',
    '#title' => t('Allow quick uploads'),
    '#default_value' => !empty($profile->settings['quickupload']) ? $profile->settings['quickupload'] : 'f',
    '#options' => array(
      'f' => t('No'),
      't' => t('Yes')
    ),
    '#description' => t('The quick upload functionality can be disabled and enabled independently of the file browser. It will always use the settings below. To enable quick uploads you must follow the same configuration procedure as when enabling the built-in file browser.'),
  );

  $current_user_files_path = empty($profile->settings['UserFilesPath']) ? "" : strtr($profile->settings['UserFilesPath'], array("%f" => file_directory_path(), "%u" => "UID", "%b" => base_path(), "%n" => "UNAME"));
  $current_user_files_absolute_path = empty($profile->settings['UserFilesAbsolutePath']) ? "" : strtr($profile->settings['UserFilesAbsolutePath'], array("%f" => file_directory_path(), "%u" => "UID", "%b" => base_path(), "%d" => $_SERVER['DOCUMENT_ROOT'], "%n" => "UNAME"));

  $form['fckeditor_upload_settings']['UserFilesPath'] = array(
    '#type' => 'textfield',
    '#title' => t('Path to uploaded files'),
    '#default_value' => !empty($profile->settings['UserFilesPath']) ? $profile->settings['UserFilesPath'] : "%b%f/",
    '#size' => 40,
    '#maxlength' => 255,
    '#description' => t('Path to uploaded files relative to the document root.<br />Available placeholders:<br/><strong>%b</strong> - base URL path of the Drupal installation (!base).<br/><strong>%f</strong> - Drupal file system path where the files are stored (!files).<br /><strong>%u</strong> - User ID.<br /><strong>%n</strong> - Username.<br />Current path: !path', array('!path' => $current_user_files_path, '!files' => file_directory_path(), '!base' => base_path())),
  );

  $form['fckeditor_upload_settings']['UserFilesAbsolutePath'] = array(
    '#type' => 'textfield',
    '#title' => t('Absolute path to uploaded files'),
    '#default_value' => !empty($profile->settings['UserFilesAbsolutePath']) ? $profile->settings['UserFilesAbsolutePath'] : "%d%b%f/",
    '#size' => 40,
    '#maxlength' => 255,
    '#description' => t('The path to the local directory (in the server) which points to the path defined above. If empty, FCKeditor will try to discover the right path.<br />Available placeholders:<br/><strong>%d</strong> - server path to document root (!root).<br /><strong>%b</strong> - base URL path of the Drupal installation (!base).<br/><strong>%f</strong> - Drupal file system path where the files are stored (!files).<br /><strong>%u</strong> - User ID.<br /><strong>%n</strong> - Username.<br />Current path: !path', array('!path' => $current_user_files_absolute_path, '!files' => file_directory_path(), '!base' => base_path(), '!root' => $_SERVER['DOCUMENT_ROOT'])),
  );

  if (variable_get('file_downloads', '') == FILE_DOWNLOADS_PRIVATE) {
    $form['fckeditor_upload_settings']['UserFilesPath']['#description'] = t('Setting relative path to uploaded files has been disabled because private downloads are enabled and this path is calculated automatically. To change the location of uploaded files in the private file system, edit the <a href="!url">FCKeditor Global Profile</a>.', array('!url' => url('admin/settings/fckeditor/editg')));
    $form['fckeditor_upload_settings']['UserFilesPath']['#disabled'] = TRUE;
    $form['fckeditor_upload_settings']['UserFilesAbsolutePath']['#description'] = t('Setting path to uploaded files has been disabled because private downloads are enabled and this path is calculated automatically.To change the location of uploaded files in the private file system, edit the <a href="!url">FCKeditor Global Profile</a>.', array('!global' => url('admin/settings/fckeditor/editg')));
    $form['fckeditor_upload_settings']['UserFilesAbsolutePath']['#disabled'] = TRUE;
  }

  $form['advanced'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced options'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['advanced']['theme_config_js'] = array(
    '#type' => 'radios',
    '#title' => t('Load fckeditor.config.js from theme path'),
    '#default_value' => !empty($profile->settings['theme_config_js']) ? $profile->settings['theme_config_js'] : 'f',
    '#options' => array(
      't' => t('Yes'),
      'f' => t('No')
    ),
    '#description' => t('When set to "true" the editor will try to load the fckeditor.config.js file from theme directory.'),
  );
  $form['advanced']['js_conf'] = array(
    '#type' => 'textarea',
    '#title' => t('Custom javascript configuration'),
    '#default_value' => !empty($profile->settings['js_conf']) ? $profile->settings['js_conf'] : "",
    '#cols' => 60,
    '#rows' => 5,
    '#description' => t('To change FCKeditor configuration globally, you should modify the config file: "!fckeditor_config". Sometimes it is required to change the FCKeditor configuration for a single profile only. Use this box to define settings that are unique for this profile. Available options are listed in the <a href="!docs">FCKeditor documentation</a>. Add the following code snippet to disable some advanced tabs in dialog windows of FCKeditor: <pre>@code</pre><strong>Warning</strong>: If you make something wrong here, FCKeditor may fail to load.', array('!fckeditor_config' => drupal_get_path('module', 'fckeditor') ."/fckeditor.config.js", '!docs' => 'http://docs.fckeditor.net/FCKeditor_2.x/Developers_Guide/Configuration/Configuration_Options', '@code' => "LinkDlgHideTarget = true;\nLinkDlgHideAdvanced = true;\nImageDlgHideLink = true;\nImageDlgHideAdvanced = true;\nFlashDlgHideAdvanced = true;")),
    '#wysiwyg' => FALSE,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save')
  );

  return $form;
}

/**
 * Profile validation.
 */
function fckeditor_admin_profile_form_validate($form, &$form_state) {
  $edit =& $form_state['values'];

  //include mode and all other fields are empty, invalid
  if ($edit['excl_mode'] == 1 && empty($edit['excl'])) {
    form_set_error('excl_mode', t('Include mode selected, but no paths given. Enter at least one path where FCKeditor should appear.'));
  }
  else {
    fckeditor_admin_profile_validate_fieldpaths('excl', $edit['excl']);
  }

  fckeditor_admin_profile_validate_fieldpaths('simple_incl', $edit['simple_incl']);

  if (!preg_match('/^\d+$/', trim($edit['min_rows']))) {
    form_set_error('min_rows', t('Minimum rows must be a valid number.'));
  }

  if ($edit['default'] == 't' && $edit['popup'] == 't') {
    form_set_error('popup', t('If FCKeditor is enabled by default, popup window must be disabled.'));
  }

  if ($edit['show_toggle'] == 't' && $edit['popup'] == 't') {
    form_set_error('popup', t('If toggle is enabled, popup window must be disabled.'));
  }

  if (!$edit['name']) {
    form_set_error('name', t('You must give a profile name.'));
  }
  elseif ($edit['name'] == 'FCKeditor Global Profile') {
    form_set_error('name', t('This profile name is reserved. Please choose a different name.'));
  }
  elseif (!isset($edit['_profile']) || ($edit['_profile']->name != $edit['name'])) {
    $result = fckeditor_profile_load($edit['name']);
    if (!empty($result)) {
      form_set_error('name', t('The profile name must be unique. A profile with this name already exists.'));
    }
  }

  if (!preg_match('/^\d+%?$/', $edit['width'])) {
    form_set_error('width', t('Enter valid width. Example: 400 or 100%.'));
  }

  if (!empty($edit['css_path'])) {
    if ($edit['css_mode'] != 'self') {
      form_set_error('css_path', t('CSS path is not empty. Please set the "Editor CSS" option to "define css" mode.'));
    }
    else if (FALSE !== strpos($edit['css_path'], '"')) {
      form_set_error('css_path', t('Double quotes are not allowed in CSS path.'));
    }

    else if (substr($edit['css_path'], 0, 1) == "'" && substr($edit['css_path'], -1) == "'") {
      form_set_error('css_path', t('Enter valid path, do not surround it with quotes.'));
    }
  }

  if (!empty($edit['styles_path'])) {
    if ($edit['css_style'] != 'self') {
      form_set_error('styles_path', t('Path to predefined styles is not empty. Please set the "Predefined styles" option to "define path to fckstyles.xml" mode.'));
    }
    else if (FALSE !== strpos($edit['styles_path'], '"')) {
      form_set_error('styles_path', t('Double quotes are not allowed in path.'));
    }
    else if (substr($edit['styles_path'], 0, 1) == "'" && substr($edit['styles_path'], -1) == "'") {
      form_set_error('styles_path', t('Enter valid path, do not surround it with quotes.'));
    }
  }

  if (!empty($edit['font_format'])) {
    if (!preg_match("/^((p|div|pre|address|h1|h2|h3|h4|h5|h6);)*(p|div|pre|address|h1|h2|h3|h4|h5|h6)$/", $edit['font_format'])) {
      form_set_error('font_format', t('Enter valid, semicolon separated, list of HTML font formats (no semicolon at the end of list expected).'));
    }
  }

  if (variable_get('file_downloads', '') !== FILE_DOWNLOADS_PRIVATE) {
    if (!empty($edit['UserFilesAbsolutePath']) && empty($edit['UserFilesPath'])) {
      form_set_error('UserFilesPath', t('Path to uploaded files is required.'));
    }
    if (!empty($edit['UserFilesPath']) && empty($edit['UserFilesAbsolutePath'])) {
      form_set_error('UserFilesPath', t('Absolute path to uploaded files is required.'));
    }
  }
}

function fckeditor_admin_profile_form_submit($form, &$form_state) {
  $edit =& $form_state['values'];

  if (isset($edit['_profile'])) {
    db_query("DELETE FROM {fckeditor_settings} WHERE name = '%s'", $edit['_profile']->name);
    db_query("DELETE FROM {fckeditor_role} WHERE name = '%s'", $edit['_profile']->name);
    drupal_set_message(t('Your FCKeditor profile has been updated.'));
  }
  else {
    drupal_set_message(t('Your FCKeditor profile has been created.'));
  }

  $settings = fckeditor_admin_values_to_settings($edit);
  db_query("INSERT INTO {fckeditor_settings} (name, settings) VALUES ('%s', '%s')", $edit['name'], $settings);
  fckeditor_rebuild_selectors($edit['name']);
  if (!empty($edit['rids'])) {
    foreach (array_keys($edit['rids']) as $rid) {
      if ($edit['rids'][$rid]!=0) {
        db_query("INSERT INTO {fckeditor_role} (name, rid) VALUES ('%s', %d)", $edit['name'], $rid);
      }
    }
  }

  $form_state['redirect'] = 'admin/settings/fckeditor';
}

function fckeditor_admin_global_profile_form($form_state, $mode = 'add') {
  module_load_include('lib.inc', 'fckeditor');
  if ($mode == 'edit') {
    $profile = fckeditor_profile_load('FCKeditor Global Profile');

    $form['_profile'] = array(
      '#type' => 'value',
      '#value' => $profile,
    );
  }
  else {
    $profile = new stdClass();
  }

  if ($mode == 'add') {
    $data = fckeditor_profile_load('FCKeditor Global Profile');
    if (!empty($data)) {
      drupal_set_message(t('Global profile already exist. Only one global profile is allowed.'), 'error');
      drupal_not_found();
    }

    $btn = t('Create global profile');
  }
  else {
    $btn = t('Update global profile');
  }

  $form['common'] = array(
    '#type' => 'fieldset',
    '#title' => t('Main setup'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE
  );

  $roles = fckeditor_sorted_roles();
  $rids = $rtext = array();
  foreach ($roles as $rid => $name) {
    $rids[] = $rid;
    $rtext[] = '<strong>'. $rid .' - </strong>'. $name;
  }
  $form['common']['rank'] = array(
    '#type' => 'textfield',
    '#title' => t('Role precedence'),
    '#default_value' => implode('>', $rids),
    '#description' => t('A user having <strong>multiple roles</strong> gets the permissions of the highest one. Sort role IDs according to their <strong>precedence from higher to lower</strong> by putting > in between.'),
  );
  if ($rids) {
    $form['common']['rank']['#description'] .= '<br />'. t('Here is the id-name pairs of roles having access to FCKeditor:') .'<div>'. implode('<br />', $rtext) .'</div>';
  }
  else {
    $form['common']['rank']['#description'] .= '<br />'. t('You haven\'t assigned the "access fckeditor" <a href="!permissions">permissions</a> yet.', array('!permissions' => url('admin/user/permissions')));
  }

  $form['fckeditor_exclude_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Visibility settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['fckeditor_exclude_settings']['excl_mode'] = array(
    '#type' => 'radios',
    '#title' => t('Use inclusion or exclusion mode'),
    '#default_value' => (empty($profile->settings['excl_mode']) || in_array($profile->settings['excl_mode'], array(0, 2))) ? 0 : 1,
    '#options' => array(
      '0' => t('Exclude'),
      '1' => t('Include')
    ),
    '#description' => t('Choose the way of disabling/enabling FCKeditor on selected fields/paths (see below). Use exclude to disable FCKeditor on selected fields/paths. Use include if you want to load FCKeditor only on selected paths/fields.'),
  );
  /**
   * get excluded fields - so we can have normal textareas too
   * split the phrase by any number of commas or space characters,
   * which include " ", \r, \t, \n and \f
   */
  $form['fckeditor_exclude_settings']['excl'] = array(
    '#type' => 'textarea',
    '#title' => t('Fields to exclude/include'),
    '#cols' => 60,
    '#rows' => 5,
    '#prefix' => '<div style="margin-left:20px">',
    '#suffix' => '</div>',
    '#default_value' => !empty($profile->settings['excl']) ? $profile->settings['excl'] : '',
    '#description' => t('Enter the paths to the textarea fields on which you want to enable or disable FCKeditor.') .' '. t('Please see the <a href="!helppagelink">help page</a> for more information about defining field names. Short instruction is available below.', array('!helppagelink' => url('admin/help/fckeditor', array('fragment' => 'fieldinclexcl')))) .' <ul><li>'. t('Path structure: <strong>content_type@path.element_id</strong>') .'</li><li>'. t('The following wildcards are available: "*", "?".') .'</li><li>'. t('Content type is optional. You may even specify only path or field id.') .'</li><li>'. t('Examples:') .'<ul><li><em>blog@*.edit-body</em> - '. t('matches all fields of type "blog" called edit-body, on any page.') .'<li><em>node/add/*.edit-user-*</em> - '. t('matches fields starting with "edit-user-" on pages starting with "node/add/') .'</li></ul></li></ul>',
    '#wysiwyg' => FALSE,
  );

  $form['fckeditor_exclude_settings']['simple_incl'] = array(
    '#type' => 'textarea',
    '#title' => t('Force simplified toolbar on the following fields'),
    '#cols' => 60,
    '#rows' => 5,
    '#default_value' => !empty($profile->settings['simple_incl']) ? $profile->settings['simple_incl'] : '',
    '#description' => t('Enter the paths to the textarea fields on which you want to force the simplified toolbar (!name).', array('!name' => FCKEDITOR_FORCE_SIMPLE_TOOLBAR_NAME)) .' '. t('Please see the <a href="!helppagelink">help page</a> for more information about defining field names. Take a look at the exclusion settings (above) for short instruction.', array('!helppagelink' => url('admin/help/fckeditor', array('fragment' => 'fieldinclexcl')))),
    '#wysiwyg' => FALSE,
  );

  $form['fckeditor_advanced_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $module_drupal_path = drupal_get_path('module', 'fckeditor');

  $form['fckeditor_advanced_settings']['fckeditor_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Path to FCKeditor'),
    '#default_value' =>  !empty($profile->settings['fckeditor_path']) ? $profile->settings['fckeditor_path'] : '%m/fckeditor',
    '#size' => 40,
    '#maxlength' => 128,
    '#description' => t('Path to FCKeditor (the HTML editor, downloaded from <a href="!fckeditornet">www.fckeditor.net</a>) relative to the document root.<br />Available placeholders:<br /><strong>%b</strong> - base URL path of the Drupal installation (!base).<br /><strong>%m</strong> - base URL path where FCKeditor module is stored (!files).<br />Current path: !path', array('!path' => fckeditor_path(FALSE), '!base' => base_path(), '!files' => base_path() . $module_drupal_path , '!fckeditornet' => 'http://www.fckeditor.net/download')),
    '#required' => TRUE
  );

  $form['fckeditor_advanced_settings']['fckeditor_local_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Local path to FCKeditor'),
    '#default_value' =>  isset($profile->settings['fckeditor_local_path'])?$profile->settings['fckeditor_local_path']:'',
    '#size' => 40,
    '#maxlength' => 128,
    '#description' => t('The path to the local directory (on the server) which points to the path defined above. Enter either an absolute server path or path relative to "index.php". If empty, FCKeditor module will try to find the right path.<br />Current path: !path', array('!path' => fckeditor_path(TRUE))),
  );

  $form['fckeditor_advanced_settings']['show_fieldnamehint'] = array(
    '#type' => 'radios',
    '#title' => t('Show field name hint below each rich text editor'),
    '#default_value' => !empty($profile->settings['show_fieldnamehint']) ? $profile->settings['show_fieldnamehint'] : 't',
    '#options' => array(
      't' => t('Yes'),
      'f' => t('No')
    ),
    '#description' => t('This only applies for users with "administer fckeditor" permissions.'),
  );

  if (variable_get('file_downloads', '') == FILE_DOWNLOADS_PRIVATE) {
    $current_private_dir = !isset($edit->settings['private_dir']) ? "" : $edit->settings['private_dir'];
    $form['fckeditor_advanced_settings']['private_dir'] = array(
      '#type' => 'textfield',
      '#title' => t('Location of files uploaded with FCKeditor in the private folder'),
      '#default_value' => $current_private_dir,
      '#size' => 40,
      '#maxlength' => 255,
      '#description' => t('The path relative to the location of the private directory where FCKeditor should store uploaded files.') .'<br />'. t('<strong>Warning:</strong> FCKeditor does not implement any kind of access protection on files available in this location. All files stored in the directory defined above might be accessible by unathenticated users if there is no information about the file in the Drupal\'s database.') .'<br />'. t('System path to the private folder is: !system_path.', array('!system_path' => realpath(file_directory_path()) . DIRECTORY_SEPARATOR)) .'<br />'. t('Available wildcard characters:<br/><strong>%u</strong> - User ID.') .'<br />'. t('Current path: !path', array('!path' => $current_private_dir .' ('. file_create_path($current_private_dir) .')')),
    );
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => $btn
  );

  return $form;
}

function fckeditor_admin_global_profile_form_validate($form, &$form_state) {
  $edit =& $form_state['values'];

  //include mode and all other fields are empty, invalid
  if ($edit['excl_mode'] == 1 && empty($edit['excl'])) {
    form_set_error('excl_mode', t('Include mode selected, but no paths given. Enter at least one path where FCKeditor should appear.'));
  }
  else {
    fckeditor_admin_profile_validate_fieldpaths('excl', $edit['excl']);
  }

  fckeditor_admin_profile_validate_fieldpaths('simple_incl', $edit['simple_incl']);
}

function fckeditor_admin_global_profile_form_submit($form, &$form_state) {
  module_load_include('lib.inc', 'fckeditor');
  $edit =& $form_state['values'];
  $edit['name'] = 'FCKeditor Global Profile';

  if (isset($edit['rank'])) {
    $edit['rank'] = explode('>', str_replace(' ', '', $edit['rank']));
  }

  if (isset($edit['_profile'])) {
    db_query("DELETE FROM {fckeditor_settings} WHERE name = '%s'", $edit['_profile']->name);
    db_query("DELETE FROM {fckeditor_role} WHERE name = '%s'", $edit['_profile']->name);
  }

  //strip whitespaces
  if (empty($edit['fckeditor_local_path'])) {
    $edit['fckeditor_local_path'] = '';
  }
  else {
    $edit['fckeditor_local_path'] = trim($edit['fckeditor_local_path']);
  }

  //strip slash from the end
  if (empty($edit['fckeditor_path'])) {
    $edit['fckeditor_path'] = '';
  }
  $edit['fckeditor_path'] = trim(rtrim($edit['fckeditor_path'], "/"));
  if ($edit['fckeditor_path'] && 0 !== strpos($edit['fckeditor_path'], "/") && 0 !== strpos($edit['fckeditor_path'], "%")) {
    //ensure that slash is at the beginning
    $edit['fckeditor_path'] = "/". $edit['fckeditor_path'];
  }
  //no slash at the end
  $edit['fckeditor_local_path'] = trim(rtrim($edit['fckeditor_local_path'], "/"));

  $settings = fckeditor_admin_values_to_settings($edit);
  db_query("INSERT INTO {fckeditor_settings} (name, settings) VALUES ('%s', '%s')", $edit['name'], $settings);
  fckeditor_rebuild_selectors($edit['name']);

  drupal_set_message(t('FCKeditor global profile has been saved.'));
  $form_state['redirect'] = 'admin/settings/fckeditor';
}

/**
 * Converts an array of form values to a serialized array that does not
 * contain Drupal Form API values
 */
function fckeditor_admin_values_to_settings($values) {
  unset($values['name'], $values['rids'], $values['_profile'], $values['op'], $values['submit'], $values['form_build_id'], $values['form_token'], $values['form_id']);
  return serialize($values);
}

function fckeditor_admin_profile_validate_fieldpaths($fieldname, $paths) {
  $myerrors = array();

  $rules = preg_split('/[\s,]+/', $paths);

  foreach ($rules as $rule) {
    $rule = trim($rule);
    if (!empty($rule) && strpos($rule, '.') === FALSE && strpos($rule, '/') === FALSE && strpos($rule, '-') === FALSE) {
      $myerrors[] = t('Rule %rule is ambiguous: please append .* if %rule is a path or prepend *. if %rule is a field', array('%rule' => $rule));
    }
  }

  if (!empty($myerrors)) {
    form_set_error($fieldname, implode('<br/>', $myerrors));
  }
}

function fckeditor_admin_profile_delete_form($form_state, $profile) {
  $form = array();

  $form['_profile'] = array(
    '#type' => 'value',
    '#value' => $profile,
  );

  $form['question'] = array(
    '#type' => 'item',
    '#value' => t('Are you sure that you want to delete the FCKeditor profile %profile?', array('%profile' => $profile->name)),
  );

  $form['delete'] = array(
    '#type' => 'submit',
    '#id' => 'delete',
    '#value' => t('Delete'),
  );

  $form['back'] = array(
    '#type' => 'submit',
    '#id' => 'back',
    '#value' => t('Cancel'),
  );

  return $form;
}

function fckeditor_admin_profile_delete_form_submit($form, &$form_state) {
  $v =& $form_state['values'];

  if ($form_state['clicked_button']['#id'] == 'delete') {
    fckeditor_profile_delete($v['_profile']->name);
    drupal_set_message(t('Deleted FCKeditor profile.'));
  }

  $form_state['redirect'] = 'admin/settings/fckeditor';
}

/**
 * Rebuilds the regular expression that is used to match the inclusion/exclusion rules
 * and the simplified toolbar rules
 *
 * @param string $name Name of the profile to process. If omitted, all profiles are rebuilt
 */
function fckeditor_rebuild_selectors($name = NULL) {
  if ($name == NULL) {
    $result = db_query("SELECT * FROM {fckeditor_settings}");
  }
  else {
    $result = db_query("SELECT * FROM {fckeditor_settings} WHERE name = '%s'", $name);
  }

  while (($data = db_fetch_object($result))) {
    if ($data->settings) {
      $settings = unserialize($data->settings);

      foreach (array('excl', 'simple_incl') as $var) {
        $settings[$var .'_regex'] = '';
        $rules = preg_split('/[\s,]+/', $settings[$var]);
        $regex = array();

        if (!empty($rules)) {
          foreach ($rules as $rule) {
            if (!empty($rule)) {
              $rule = fckeditor_parse_rule($rule);
              $regex[] = '(?:'. fckeditor_rule_to_regex($rule) .')';
            }
          }

          if (!empty($regex)) {
            $settings[$var .'_regex'] = '#'. implode('|', $regex) .'#';
          }
        }
      }

      db_query("UPDATE {fckeditor_settings} SET settings='%s' WHERE name='%s'", serialize($settings), $data->name);
    }
  }
}

function fckeditor_rule_create($nodetype = '*', $path = '*', $fieldname = '*') {
  $rule = new stdClass();
  $rule->nodetype = $nodetype;
  $rule->path = $path;
  $rule->field = $fieldname;

  return $rule;
}

function fckeditor_parse_rule($rule) {
  $ruleobj = new stdClass();

  $atpos = strpos($rule, '@');
  if ($atpos !== FALSE) {
    $ruleobj->nodetype = substr($rule, 0, $atpos);
    $rule = substr($rule, $atpos + 1);
  }
  else {
    $ruleobj->nodetype = '*';
  }

  $dotpos = strpos($rule, '.');
  if ($dotpos === FALSE) {
    if (strpos($rule, '/') === FALSE && strpos($rule, '-') !== FALSE) {
      // assume it's a field
      $ruleobj->path = '*';
      $ruleobj->field = $rule;
    }
    elseif (strpos($rule, '/') !== FALSE) {
      // assume it's a path
      $ruleobj->path = $rule;
      $ruleobj->field = '*';
    }
    else {
      return NULL;
    }
  }
  else {
    $ruleobj->path = substr($rule, 0, $dotpos);
    $ruleobj->field = str_replace('\.', '.', substr($rule, $dotpos + 1));
  }

  return $ruleobj;
}

function fckeditor_rule_to_regex($rule) {
  static $replace = array('\*' => '.*', '\?' => '.');

  $field = str_replace('.', '\.', $rule->field);
  $regex = '^'. preg_quote($rule->nodetype, '#') .'@'. preg_quote($rule->path, '#') .'\.'. preg_quote($field, '#') .'$';
  $regex = strtr($regex, $replace);

  return $regex;
}

function fckeditor_rule_to_string($rule) {
  $field = str_replace('.', '\.', $rule->field);
  $rulestr = '';
  if ($rule->nodetype != '*') {
    $rulestr .= $rule->nodetype .'@';
  }
  return $rulestr . $rule->path .'.'. $field;
}

/**
 * Remove a profile from the database.
 */
function fckeditor_profile_delete($name) {
  db_query("DELETE FROM {fckeditor_settings} WHERE name = '%s'", $name);
  db_query("DELETE FROM {fckeditor_role} WHERE name = '%s'", $name);
}

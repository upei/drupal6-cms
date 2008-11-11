<?php
// $Id: tinymce.module,v 1.90.4.23 2007/05/06 01:41:35 m3avrck Exp $
// A collaborative project by Matt Westgate <drupal at asitis dot org>,
// Richard Bennett <richard.b@ at ritechnologies dot com> and Jeff Robbins <robbins at jjeff dot com>

/**
 * @file
 * Admin interface for TinyMCE module.
 */
 
/**
 * Controller for tinymce administrative settings.
 */
function tinymce_admin($arg = NULL) {

  $edit = $_POST;
  $op = isset($_POST['op']) ? $_POST['op'] : NULL;
  $op = $arg && !$op ? $arg : $op;

  switch ($op) {
    case 'add':
      $breadcrumb[] = l(t('Home'), NULL);
      $breadcrumb[] = l(t('Administer'), 'admin');
      $breadcrumb[] = l(t('Site configuration'), 'admin/settings');
      $breadcrumb[] = l(t('TinyMCE'), 'admin/settings/tinymce');
      $breadcrumb[] = l(t('Add new TinyMCE profile'), 'admin/settings/tinymce/add');
      drupal_set_breadcrumb($breadcrumb);
      $output = tinymce_profile_form($edit);
      break;

    case 'edit':
      drupal_set_title(t('Edit tinymce profile'));
      $output = tinymce_profile_form(tinymce_profile_load(urldecode(arg(4))));
      break;

    case 'delete':
      tinymce_profile_delete(urldecode(arg(4)));
      drupal_set_message(t('Deleted profile'));
      drupal_goto('admin/settings/tinymce');
      break;

    case t('Create profile');
    case t('Update profile');
      if (tinymce_profile_validate($edit)) {
        tinymce_profile_save($edit);
        $edit['old_name'] ? drupal_set_message(t('Your TinyMCE profile has been updated.')) : drupal_set_message(t('Your TinyMCE profile has been created.'));
        drupal_goto('admin/settings/tinymce');
      }
      else {
        $output = tinymce_profile_form($edit);
      }
      break;

    default:
      drupal_set_title(t('TinyMCE settings'));
      //Check if TinyMCE is installed.
      $tinymce_loc = drupal_get_path('module', 'tinymce') .'/tinymce/';
      if (!is_dir($tinymce_loc)) {
        drupal_set_message(t('Could not find the TinyMCE engine installed at <strong>!tinymce-directory</strong>. Please <a href="http://tinymce.moxiecode.com/">download TinyMCE</a>, uncompress it and copy the folder into !tinymce-path.', array('!tinymce-path' => drupal_get_path('module', 'tinymce'), '!tinymce-directory' => $tinymce_loc)), 'error');
      }
      $output = tinymce_profile_overview();
  }

  return $output;
}

/**
 * Return an HTML form for profile configuration.
 */
function tinymce_profile_form_build($form_state, $edit) {
  $edit = (object) $edit;

  // Only display the roles that currently don't have a tinymce profile. One
  // profile per role.
  $orig_roles = user_roles(FALSE, 'access tinymce');
  $roles = $orig_roles;
  if (arg(3) == 'add') {
    $result = db_query('SELECT DISTINCT(rid) FROM {tinymce_role}');
    while ($data = db_fetch_object($result)) {
      if (!in_array($data->rid, array_keys((array) $edit->rids)) && !form_get_errors()) {
        unset($roles[$data->rid]);
      }
    }
    if (!$orig_roles) {
      drupal_set_message(t('You must <a href="!access-control-url">assign</a> at least one role with the \'access tinymce\' permission before creating a profile.', array('!access-control-url' => url('admin/user/permissions'))), 'error');
    }
    else if (!$roles) {
      drupal_set_message(t('You will not be allowed to create a new profile since all user roles have already been assigned profiles. Either remove an existing tinymce profile from at least one role or assign another role the \'access tinymce\' permission.'), 'error');
    }
    else if (count($orig_roles) != count($roles)) {
      drupal_set_message(t('Not all user roles are shown since they already have tinymce profiles. You must first unassign profiles in order to add them to a new one.'));
    }
    $btn = t('Create profile');
  }
  else {
    $form['old_name'] = array('#type' => 'hidden', '#value' => $edit->name);
    $btn = t('Update profile');
  }

  $form['basic'] = array(
    '#type' => 'fieldset',
    '#title' => t('Basic setup'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE
  );

  $form['basic']['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Profile name'),
    '#default_value' => isset($edit->name) ? $edit->name : NULL,
    '#size' => 40,
    '#maxlength' => 128,
    '#description' => t('Enter a name for this profile. This name is only visible within the tinymce administration page.'),
    '#required' => TRUE
  );

  $form['basic']['rids'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Roles allowed to use this profile'),
    '#default_value' => isset($edit->rids) ? array_keys((array) $edit->rids) : NULL,
    '#options' => $roles,
    '#description' =>  t('Check at least one role. Only roles with \'access tinymce\' permission will be shown here.'),
    '#required' => TRUE
  );

  $form['basic']['default'] = array(
    '#type' => 'select',
    '#title' => t('Default state'),
    '#default_value' => isset($edit->settings['default']) ? $edit->settings['default'] : 'false',
    '#options' => array('false' => t('disabled'), 'true' => t('enabled')),
    '#description' => t('Default editor state for users in this profile. Users will be able to override this state if the next option is enabled.'),
  );

  $form['basic']['user_choose'] = array(
    '#type' => 'select',
    '#title' => t('Allow users to choose default'),
    '#default_value' => isset($edit->settings['user_choose']) ? $edit->settings['user_choose'] : 'false',
    '#options' => array('false' => t('false'), 'true' => t('true')),
    '#description' => t('If allowed, users will be able to choose their own TinyMCE default state by visiting their profile page.'),
  );

  $form['basic']['show_toggle'] = array(
    '#type' => 'select',
    '#title' => t('Show disable/enable rich text editor toggle'),
    '#default_value' => isset($edit->settings['show_toggle']) ? $edit->settings['show_toggle'] : 'true',
    '#options' => array('false' => t('false'), 'true' => t('true')),
    '#description' => t('Whether or not to show the disable/enable rich text editor toggle below the textarea. If false, editor defaults to the global default or user default (see above).'),
  );

  // This line upgrades previous versions of TinyMCE for user who previously selected a theme other than advanced.
  if (isset($edit->settings['theme']) && $edit->settings['theme'] != 'advanced')
    $edit->settings['theme'] = 'advanced';

  $form['basic']['theme'] = array(
    '#type' => 'hidden',
    '#value' => isset($edit->settings['theme']) ? $edit->settings['theme'] : 'advanced'
  );

  $form['basic']['language'] = array(
    '#type' => 'select',
    '#title' => t('Language'),
    '#default_value' => isset($edit->settings['language']) ? $edit->settings['language'] : 'en',
    '#options' => drupal_map_assoc(array('ar', 'ca', 'cs', 'cy', 'da', 'de', 'el', 'en', 'es', 'fa', 'fi', 'fr', 'fr_ca', 'he', 'hu', 'is', 'it', 'ja', 'ko', 'nb', 'nl', 'nn', 'pl', 'pt', 'pt_br', 'ru', 'ru_KOI8-R', 'ru_UTF-8', 'si', 'sk', 'sv', 'th', 'zh_cn', 'zh_tw', 'zh_tw_utf8')),
    '#description' => t('The language for the TinyMCE interface. Language codes based on the <a href="http://www.loc.gov/standards/iso639-2/englangn.html">ISO-639-2</a> format.')
  );

  $form['basic']['safari_message'] = array(
    '#type' => 'select',
    '#title' => t('Safari browser warning'),
    '#default_value' => isset($edit->settings['safari_message']) ? $edit->settings['safari_message'] : 'false',
    '#options' => array('false' => t('false'), 'true' => t('true')),
    '#description' => t('TinyMCE support for the Safari web browser is experimental and a warning message is displayed when that browser is detected. You can disable this message here.')
  );

  $form['visibility'] = array(
    '#type' => 'fieldset',
    '#title' => t('Visibility'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE
  );

  $access = user_access('use PHP for block visibility');

  // If the visibility is set to PHP mode but the user doesn't have this block permission, don't allow them to edit nor see this PHP code
  if (isset($edit->settings['access']) && $edit->settings['access'] == 2 && !$access) {
    $form['visibility'] = array();
    $form['visibility']['access'] = array(
      '#type' => 'value',
      '#value' => 2
    );
    $form['visibility']['access_pages'] = array(
      '#type' => 'value',
      '#value' => isset($edit->settings['access_pages']) ? $edit->settings['access_pages'] : NULL
    );
  }
  else {
    $options = array(t('Show on every page except the listed pages.'), t('Show on only the listed pages.'));
    $description = t("Enter one page per line as Drupal paths. The '*' character is a wildcard. Example paths are '!blog' for the blog page and !blog-wildcard for every personal blog. !front is the front page.", array('!blog' => theme('placeholder', 'blog'), '!blog-wildcard' =>  theme('placeholder', 'blog/*'), '!front' => theme('placeholder', '<front>')));

    if ($access) {
      $options[] = t('Show if the following PHP code returns <code>TRUE</code> (PHP-mode, experts only).');
      $description .= t('If the PHP-mode is chosen, enter PHP code between !php. Note that executing incorrect PHP-code can break your Drupal site.', array('!php' => theme('placeholder', '<?php ?>')));
    }
    $form['visibility']['access'] = array(
      '#type' => 'radios',
      '#title' => t('Show tinymce on specific pages'),
      '#default_value' => isset($edit->settings['access']) ? $edit->settings['access'] : 1,
      '#options' => $options
    );
    $form['visibility']['access_pages'] = array(
      '#type' => 'textarea',
      '#title' => t('Pages'),
      '#default_value' => isset($edit->settings['access_pages']) ? $edit->settings['access_pages'] : tinymce_help('admin/settings/tinymce#pages', NULL),
      '#description' => $description
    );
  }

  $form['buttons'] = array(
    '#type' => 'fieldset',
    '#title' => t('Buttons and plugins'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#tree' => TRUE,
    '#theme' => 'tinymce_admin_button_table'
  );

  $metadata = _tinymce_get_buttons(FALSE);
  // Generate the button list.
  foreach ($metadata as $name => $meta) {
    if (isset($meta['buttons']) && is_array($meta['buttons'])) {
      foreach ($meta['buttons'] as $button) {
        if ($name != 'default') {
          $img_src = drupal_get_path('module', 'tinymce') ."/tinymce/jscripts/tiny_mce/plugins/$name/images/$name.gif";

          //correct for plugins that have more than one button
          if (!file_exists($img_src)) {
            $img_src = drupal_get_path('module', 'tinymce') ."/tinymce/jscripts/tiny_mce/plugins/$name/images/$button.gif";
          }
        }
        else {
          $img_src = drupal_get_path('module', 'tinymce') ."/tinymce/jscripts/tiny_mce/themes/advanced/images/$button.gif";
        }

        $b = file_exists($img_src) ? '<img src="'. base_path() . $img_src .'" title="'. $button .'" style="border: 1px solid grey; vertical-align: middle;" />' : $button;

        if ($name == 'default') {
          $title = $b;
        }
        else {
          $title = isset($metadata[$name]['longname']) ? $metadata[$name]['longname'] : $name;
          if (isset($metadata[$name]['infourl'])) {
            $title = '<a href="'. $metadata[$name]['infourl'] .'" target="_blank">'. $title .'</a>';
          }
          $title = $b .' &#8211; '. $title;
        }
        $form_value = isset($edit->settings['buttons'][$name .'-'. $button]) ? isset($edit->settings['buttons'][$name .'-'. $button]) : NULL;
        $form['buttons'][$name .'-'. $button] = array('#type' => 'checkbox', '#title' => $title, '#default_value' => $form_value);
      }
    }
    else {
      $title = $metadata[$name]['longname'] ? $metadata[$name]['longname'] : $name;
      if ($metadata[$name]['infourl']) {
        $title = '<a href="'. $metadata[$name]['infourl'] .'" target="_blank">'. $title .'</a>';
      }
      $form_value = isset($edit->settings['buttons'][$name]) ? $edit->settings['buttons'][$name] : NULL;
      $form['buttons'][$name] = array('#type' => 'checkbox', '#title' => $title, '#default_value' => $form_value);
    }
  }

  $form['appearance'] = array(
    '#type' => 'fieldset',
    '#title' => t('Editor appearance'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE
  );

  $form['appearance']['toolbar_loc'] = array(
    '#type' => 'select',
    '#title' => t('Toolbar location'),
    '#default_value' => isset($edit->settings['toolbar_loc']) ? $edit->settings['toolbar_loc'] : NULL,
    '#options' => array('bottom' => t('bottom'), 'top' => t('top')),
    '#description' => t('Show toolbar at the top or bottom of the editor area?')
  );

  $form['appearance']['toolbar_align'] = array(
    '#type' => 'select',
    '#title' => t('Toolbar alignment'),
    '#default_value' => isset($edit->settings['toolbar_align']) ? $edit->settings['toolbar_align'] : NULL,
    '#options' => array('center' => t('center'), 'left' => t('left'), 'right' => t('right')),
    '#description' => t('Align tool icons left, center, or right within the toolbar.')
  );

  $form['appearance']['path_loc'] = array(
    '#type' => 'select',
    '#title' => t('Path location'),
    '#default_value' => isset($edit->settings['path_loc']) ? $edit->settings['path_loc'] : 'bottom',
    '#options' => array('none' => t('none'), 'top' => t('top'), 'bottom' => t('bottom')),
    '#description' => t('Path to html elements (i.e. "body>table>tr>td"). Show at top, bottom, or not at all.')
  );

  $form['appearance']['resizing'] = array(
    '#type' => 'select',
    '#title' => t('Enable resizing button'),
    '#default_value' => isset($edit->settings['resizing']) ? $edit->settings['resizing'] : 'true',
    '#options' => array('false' => t('false'), 'true' => t('true')),
    '#description' => t(' This option gives you the ability to enable/disable the resizing button. If enabled the <strong>Path location toolbar</strong> must be set to "top" or "bottom" in order to display the resize icon.')
  );

  $form['appearance']['block_formats'] = array(
    '#type' => 'textfield',
    '#title' => t('Block formats'),
    '#default_value' => isset($edit->settings['block_formats']) ? $edit->settings['block_formats'] : 'p,address,pre,h1,h2,h3,h4,h5,h6',
    '#size' => 40,
    '#maxlength' => 250,
    '#description' => t('Comma separated list of HTML block formats. You can only remove elements, not add.')
  );

  $form['output'] = array(
    '#type' => 'fieldset',
    '#title' => t('Cleanup and output'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE
  );

  $form['output']['verify_html'] = array(
    '#type' => 'select',
    '#title' => t('Verify HTML'),
    '#default_value' => isset($edit->settings['verify_html']) ? $edit->settings['verify_html'] : NULL,
    '#options' => array('false' => t('false'), 'true' => t('true')),
    '#description' => t('Should the HTML contents be verified or not? Verifying will strip &lt;head&gt tags, so choose false if you will be editing full page HTML.')
  );

  $form['output']['preformatted'] = array(
    '#type' => 'select',
    '#title' => t('Preformatted'),
    '#default_value' => isset($edit->settings['preformatted']) ? $edit->settings['preformatted'] : NULL,
    '#options' => array('false' => t('false'), 'true' => t('true')),
    '#description' => t('If this option is set to true, the editor will insert TAB characters on tab and preserve other whitespace characters just like a PRE HTML element does.')
  );

  $form['output']['convert_fonts_to_spans'] = array(
    '#type' => 'select',
    '#title' => t('Convert &lt;font&gt; tags to styles'),
    '#default_value' => isset($edit->settings['convert_fonts_to_spans']) ? $edit->settings['convert_fonts_to_spans'] : NULL,
    '#options' => array('true' => t('true'), 'false' => t('false')),
    '#description' => t('If you set this option to true, font size, font family, font color and font background color will be replaced by inline styles.')
  );

  $form['output']['remove_linebreaks'] = array(
     '#type' => 'select',
     '#title' => t('Remove linebreaks'),
     '#default_value' => isset($edit->settings['remove_linebreaks']) ? $edit->settings['remove_linebreaks']: NULL,
     '#options' => array('true' => 'true', 'false' => 'false'),
     '#description' => t('Set this option to false to prevent TinyMCE from removing linebreaks from existing nodes.  True avoids conflicts with some filters.')
  );

  $form['output']['apply_source_formatting'] = array(
     '#type' => 'select',
     '#title' => t('Apply source formatting'),
     '#default_value' => isset($edit->settings['apply_source_formatting']) ? $edit->settings['apply_source_formatting'] : NULL,
     '#options' => array('true' => 'true', 'false' => 'false'),
     '#description' => t('This option makes TinyMCE apply source formatting.  Set this to true for a cleaner HTML source.  Choose false to avoid conflicts with some filters.')
  );

  $form['css'] = array(
    '#type' => 'fieldset',
    '#title' => t('CSS'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE
  );

  $form['css']['css_setting'] = array(
    '#type' => 'select',
    '#title' => t('Editor CSS'),
    '#default_value' => isset($edit->settings['css_setting']) ? $edit->settings['css_setting'] : 'theme',
    '#options' => array('theme' => t('use theme css'), 'self' => t('define css'), 'none' => t('tinyMCE default')),
    '#description' => t('Defines the CSS to be used in the editor area.<br />use theme css - load style.css from current site theme.<br/>define css - enter path for css file below.<br />tinyMCE default - uses default CSS from editor.')
  );

  $form['css']['css_path'] = array(
    '#type' => 'textfield',
    '#title' => t('CSS path'),
    '#default_value' => isset($edit->settings['css_path']) ? $edit->settings['css_path'] : NULL,
    '#size' => 40,
    '#maxlength' => 255,
    '#description' => t('Enter path to CSS file (<em>example: "css/editor.css"</em>) or a list of css files seperated by a comma (<em>example: /themes/garland/style.css,http://domain.com/customMCE.css</em>).<br />Macros: %h (host name: http://www.example.com/), %t (path to theme: theme/yourtheme/)<br />Be sure to select "define css" above.')
  );

  $form['css']['css_classes'] = array(
    '#type' => 'textfield',
    '#title' => t('CSS classes'),
    '#default_value' => isset($edit->settings['css_classes']) ? $edit->settings['css_classes'] : NULL,
    '#size' => 40,
    '#maxlength' => 255,
    '#description' => t('Adds CSS classes to the "styles" droplist. Format is: &lt;title&gt;=&lt;class&gt;;<br/> Example: Header 1=header1;Header 2=header2;Header 3=header3 (note: no trailing \';\')<br />Leave blank to automatically import list of CSS classes from style sheet.')
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => $btn
  );

  return $form;
}

/**
 * Layout for the buttons in the tinymce profile form
 */
function theme_tinymce_admin_button_table($form) {

  $buttons = array();

  // Flatten forms array
  foreach (element_children($form) as $key) {
    $buttons[] = drupal_render($form[$key]);
  }

  //split checkboxes into rows with 3 columns
  $total = count($buttons);
  $rows = array();
  for ($i = 0; $i < $total; $i++) {
    $row = array();
    $row[] = array('data' => $buttons[$i]);
    $row[] = array('data' => $buttons[++$i]);
    $row[] = array('data' => $buttons[++$i]);
    $rows[] = $row;
  }

  $output = theme('table', array(), $rows, array('width' => '100%'));

  return $output;
}

/**
 * Controller for tinymce profiles.
 */
function tinymce_profile_overview() {
  $output = '';

  $profiles = tinymce_profile_load();
  if ($profiles) {
    $roles = user_roles();
    $header = array(t('Profile'), t('Roles'), t('Operations'));
    foreach ($profiles as $p) {
      $rows[] = array(array('data' => $p->name, 'valign' => 'top'), array('data' => implode("<br />\n", $p->rids)), array('data' => l(t('edit'), 'admin/settings/tinymce/edit/'. urlencode($p->name)) .' '. l(t('delete'), 'admin/settings/tinymce/delete/'. urlencode($p->name)), 'valign' => 'top'));
    }
    $output .= theme('table', $header, $rows);
    $output .= t('<p><a href="!create-profile-url">Create new profile</a></p>', array('!create-profile-url' => url('admin/settings/tinymce/add')));
  }
  else {
    drupal_set_message(t('No profiles found. Click here to <a href="!create-profile-url">create a new profile</a>.', array('!create-profile-url' => url('admin/settings/tinymce/add'))));
  }

  return $output;
}

/**
 * Save a profile to the database.
 */
function tinymce_profile_save($edit) {
  db_query("DELETE FROM {tinymce_settings} WHERE name = '%s' or name = '%s'", $edit['name'], $edit['old_name']);
  db_query("DELETE FROM {tinymce_role} WHERE name = '%s' or name = '%s'", $edit['name'], $edit['old_name']);
  db_query("INSERT INTO {tinymce_settings} (name, settings) VALUES ('%s', '%s')", $edit['name'], serialize($edit));
  foreach ($edit['rids'] as $rid => $value) {
    db_query("INSERT INTO {tinymce_role} (name, rid) VALUES ('%s', %d)", $edit['name'], $rid);
  }

  // if users can't set their own defaults, make sure to remove $user->tinymce_status so their default doesn't override the main default
  if ($edit['user_choose'] == 'false') {
    global $user;
    user_save($user, array('tinymce_status' => NULL));
  }
}

/**
 * Profile validation.
 */
function tinymce_profile_validate($edit) {
  $errors = array();

  if (!isset($edit['name'])) {
    $errors['name'] = t('You must give a profile name.');
  }

  if (!isset($edit['rids'])) {
    $errors['rids'] = t('You must select at least one role.');
  }

  foreach ($errors as $name => $message) {
    form_set_error($name, $message);
  }

  return count($errors) == 0;
}

/**
 * Remove a profile from the database.
 */
function tinymce_profile_delete($name) {
  db_query("DELETE FROM {tinymce_settings} WHERE name = '%s'", $name);
  db_query("DELETE FROM {tinymce_role} WHERE name = '%s'", $name);
}

/**
 * Return an HTML form for profile configuration.
 */
function tinymce_profile_form($edit) {

  $output = drupal_get_form('tinymce_profile_form_build', $edit);

  return $output;
}

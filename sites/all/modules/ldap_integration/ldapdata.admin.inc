<?php
// $Id: ldapdata.admin.inc,v 1.1.2.12 2008/10/14 22:09:50 miglius Exp $

/**
 * @file
 * Module admin page callbacks.
 */

//////////////////////////////////////////////////////////////////////////////
// ldapdata settings

/**
 * Implements the LDAP servers list.
 *
 * @return
 *   The HTML table with the servers list.
 */
function ldapdata_admin_list() {
  $rows = array();
  $result = db_query("SELECT sid, name FROM {ldapauth} WHERE status = '1' ORDER BY name");
  while ($row = db_fetch_object($result)) {
    $rows[] = array(
      $row->name,
      l(t('edit'), 'admin/settings/ldap/ldapdata/edit/'. $row->sid),
      l(t('reset'), 'admin/settings/ldap/ldapdata/reset/'. $row->sid),
    );
  }

  $header = array(
    t('LDAP Config'),
    array('data' => t('Operations'), 'colspan' => 2),
  );

  return theme('table', $header, $rows);
}

/**
 * Implements the LDAP server edit page.
 *
 * @param $form_state
 *   A form state array.
 * @param $op
 *   An operatin - edit or reset.
 * @param $sid
 *   A LDAP server ID.
 *
 * @return
 *   The form structure.
 */
function ldapdata_admin_edit(&$form_state, $op, $sid) {
  if ($op == "reset" && $sid) {
    $form['sid'] = array(
      '#type' => 'value',
      '#value' => $sid,
      );
    return confirm_form(
      $form,
      t('Are you sure you want to reset the fields mapping to defaults ?'),
      'admin/settings/ldap/ldapdata',
      t('<em>This action cannot be undone.</p>'),
      t('Reset'),
      t('Cancel')
    );
  }
  elseif ($op == "edit" && $sid) {
    $row = db_fetch_array(db_query("SELECT ldapdata_mappings, ldapdata_roattrs, ldapdata_rwattrs, ldapdata_binddn, ldapdata_bindpw FROM {ldapauth} WHERE sid = %d", $sid));

    $mappings = unserialize($row['ldapdata_mappings']);
    $roattrs = unserialize($row['ldapdata_roattrs']);
    $rwattrs = unserialize($row['ldapdata_rwattrs']);
    $binddn = $row['ldapdata_binddn'];
    $bindpw = $row['ldapdata_bindpw'];

    // Attribute mapping.
    $form['ldap_attribute_mapping'] = array(
      '#type' => 'fieldset',
      '#title' => t('Drupal-LDAP fields mapping'),
      '#description' => t('<p><strong style="color: red;">PLEASE NOTE</strong>: advanced configuration for this module can be set by editing the module\'s config file, located at <em style="font-style: normal; padding: 1px 3px; border: 1px solid #8888CC; background-color: #DDDDFF">modules/ldap_integration/ldap_integration/ldapdata.conf.php</em> in your Drupal install.</p>'),
      '#collapsible' => TRUE
    );
    $form['ldap_attribute_mapping']['ldap_attr_mapping'] = array(
      '#type' => 'radios',
      '#title' => t('Should Drupal account fields be mapped to LDAP Attributes?'),
      '#default_value' => $mappings['access'] ? $mappings['access'] : LDAPDATA_MAP_ATTRIBUTES,
      '#options' => array(
        LDAPDATA_MAP_ATTRIBUTES => t('Changes in account fields will be mapped to LDAP attributes and back.'),
        LDAPDATA_MAP_ATTRIBUTES_READ_ONLY => t('Same, but read-only mode.'),
        LDAPDATA_MAP_NOTHING => t('No attribute mapping will be done at all (<strong><em>Clears any existing mappings</em></strong>).'),
      ),
    );
    $profile_fields = _ldapdata_retrieve_profile_fields();
    $standard_fields = _ldapdata_retrieve_standard_user_fields();
    $drupal_fields = $profile_fields + $standard_fields;
    $form['ldap_attribute_mapping']['ldap_drupal_reverse_mapping_pre'] = array(
      '#value' => t('<div class="form-item"><label>If you selected the first or the second option above, please specify here: </label><table><thead><tr><th> Drupal field</th><th>LDAP attribute</th></tr></thead><tbody>'),
    );
    $ldap_drupal_reverse_mappings = _ldapdata_reverse_mappings($sid);
    foreach ($drupal_fields as $key => $field) {
      $field_tmp = "ldap_amap-". $key;
      $_prefix = "<tr><td><label for=\"edit[$field_tmp]\">$field</label></td><td>";
      $form['ldap_attribute_mapping'][$field_tmp] = array(
        '#type' => 'textfield',
        //'#default_value' => $ldap_drupal_reverse_mappings[$key],
        '#default_value' => isset($mappings[$field_tmp]) ? $mappings[$field_tmp] : NULL,
        '#size' => '20',
        '#prefix' => $_prefix,
        '#suffix' => '</td>',
      );
    }
    $form['ldap_attribute_mapping']['ldap_drupal_reverse_mappings_post'] = array(
      '#value' => '</tbody></table></div>',
    );

    // Attribute access control.
    $form["ldap_editable_attributes"] = array(
      '#type' => 'fieldset',
      '#title' => t('Attribute visibility & access control'),
      '#collapsible' => TRUE,
      '#description' => t('<p>Users may be able to view their LDAP attributes\' values, as well as edit them. You can configure this feature here.</p>'),
      '#tree' => TRUE,
    );
    foreach (ldapdata_attributes() as $key => $field) {
      $fields[$key] = $field[2];
    }
    $ro_status = $rw_status = array();
    foreach ($fields as $attr => $attr_name) {
      $ro_options[$attr]  = '';
      $rw_options[$attr]  = '';

      if (!empty($roattrs) && (in_array($attr, $roattrs)))
        $ro_status[] = $attr;
      if (!empty($rwattrs) && (in_array($attr, $rwattrs)))
        $rw_status[] = $attr;

      $form['ldap_editable_attributes']['ldap_attr_table'][$attr] = array(
        '#value' => $attr_name,
      );
    }
    $form['ldap_editable_attributes']['ro_status'] = array(
      '#type' => 'checkboxes',
      '#options' => $ro_options,
      '#default_value' => $ro_status,
    );
    $form['ldap_editable_attributes']['rw_status'] = array(
      '#type' => 'checkboxes',
      '#options' => $rw_options,
      '#default_value' => $rw_status,
    );
    $form['ldap_editable_attributes']['header'] = array(
      '#type' => 'value',
      '#value' => array(
        array('data' => t('Attribute Name')),
        array('data' => t('Readable by User?')),
        array('data' => t('Editable by User?')),
      )
    );

    // Advanced configuration.
    $form['advanced'] = array(
      '#type' => 'fieldset',
      '#title' => t('Advanced configuration'),
      '#description' => t('<p>When reading/editing attributes, this module logs on to the LDAP directory using the user\'s DN//pass pair. However, many LDAP setups do not allow their users to edit attributes.</p><p>If this is your case, but still you want users to edit their LDAP attributes via Drupal, you should set up an special user on your directory, with special access to edit your users\' attributes. Then this module will use it to log on and edit data.</p><p>"Test" tries authentication with the saved DN and password and prints the result.</p>'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE
    );
    $form['advanced']['ldapdata_binddn'] = array(
      '#type' => 'textfield',
      '#title' => t('DN for reading/editing attributes'),
      '#default_value' => $binddn,
      '#size' => 50,
      '#maxlength' => 255,
    );
    if (!$bindpw) {
      $form['advanced']['ldapdata_bindpw'] = array(
        '#type' => 'password',
        '#title' => t('Password for reading/editing attributes'),
        '#size' => 50,
        '#maxlength' => 255,
      );
    }
    else {
      // Given an option to clear the password.
      $form['advanced']['ldapdata_bindpw_clear'] = array(
        '#type' => 'checkbox',
        '#default_value' => FALSE,
        '#title' => t('Clear current password'),
      );
    }
    $form['advanced']['test'] = array(
      '#type'  => 'submit',
      '#value' => t('Test'),
    );

    $form['sid'] = array(
      '#type' => 'hidden',
      '#value' => $sid,
    );

    $form['buttons']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Update'),
    );

    return $form;
  }
  else {
    drupal_goto('admin/settings/ldap/ldapdata');
  }
}

/**
 * Submit hook for the settings form.
 */
function ldapdata_admin_edit_submit($form, &$form_state) {
  $op = $form_state['clicked_button']['#value'];
  $values = $form_state['values'];
  switch ($op) {
    case t('Update'):

      // Attribute mapping.
      $attr_mapping_access = $values['ldap_attr_mapping'];
      $attr_mappings['access'] = $attr_mapping_access;

      if ($attr_mapping_access >= 4) {
        foreach (element_children($values) as $attr) {
          if (preg_match("/ldap_amap/", $attr) && $values[$attr]) {
            $attr_mappings[$attr] = $values[$attr];
          }
        }
      }
      $serialized_data = serialize($attr_mappings);

      // Attribute access control.
      $ro_tmp = is_array($values['ldap_editable_attributes']['ro_status']) ? array_filter($values['ldap_editable_attributes']['ro_status']) : array();

      if (!empty($ro_tmp)) {
        foreach ($ro_tmp as $ro_attr) {
          $ro_attrs[] = $ro_attr;
        }
        $serialized_ro_attrs = serialize($ro_attrs);
      }
      $serialized_ro_attrs = isset($serialized_ro_attrs) ? $serialized_ro_attrs : NULL;

      $rw_tmp = is_array($values['ldap_editable_attributes']['rw_status']) ? array_filter($values['ldap_editable_attributes']['rw_status']) : array();

      if (!empty($rw_tmp)) {
        foreach ($rw_tmp as $rw_attr) {
          $rw_attrs[] = $rw_attr;
        }
        $serialized_rw_attrs = serialize($rw_attrs);
      }
      $serialized_rw_attrs = isset($serialized_rw_attrs) ? $serialized_rw_attrs : NULL;

      if (isset($values['ldapdata_bindpw_clear'])) {
        db_query("UPDATE {ldapauth} SET ldapdata_mappings = '%s', ldapdata_roattrs = '%s', ldapdata_rwattrs = '%s', ldapdata_binddn = '%s' WHERE sid = %d", $serialized_data, $serialized_ro_attrs, $serialized_rw_attrs, $values['ldapdata_binddn'], $values['sid']);
        if ($values['ldapdata_bindpw_clear']) {
          db_query("UPDATE {ldapauth} SET ldapdata_bindpw = '' WHERE sid = %d", $values['sid']);
        }
      }
      else {
        db_query("UPDATE {ldapauth} SET ldapdata_mappings = '%s', ldapdata_roattrs = '%s', ldapdata_rwattrs = '%s', ldapdata_binddn = '%s', ldapdata_bindpw = '%s' WHERE sid = %d", $serialized_data, $serialized_ro_attrs, $serialized_rw_attrs, $values['ldapdata_binddn'], $values['ldapdata_bindpw'], $values['sid']);
      }
      drupal_set_message(t('The configuration options have been saved.'));
      $form_state['redirect'] = 'admin/settings/ldap/ldapdata';
      break;
    case t('Reset'):
      if ($values['confirm'] == 1) {

        // Settings reset.
        db_query("UPDATE {ldapauth} SET ldapdata_mappings = '', ldapdata_roattrs = '', ldapdata_rwattrs = '', ldapdata_binddn = '', ldapdata_bindpw = '' WHERE sid = %d", $values['sid']);
        drupal_set_message(t('The configuration options have been reset to their default values.'));
      }
      $form_state['redirect'] = 'admin/settings/ldap/ldapdata';
      break;
    case t('Test'):
      global $_ldapdata_ldap;
      $user = (object)array();
      if (isset($values['sid']) && _ldapdata_init($user, $values['sid'])) {
        // Try to authenticate.
        $bind_info = _ldapdata_edition($user, $values['sid']);
        if (!$_ldapdata_ldap->connect($bind_info['dn'], $bind_info['pass'])) {
          drupal_set_message(t('Authentication with the LDAP server for the dn %dn and saved password failed.', array('%dn' => $bind_info['dn'])), 'error');
        }
        else {
          drupal_set_message(t('Authentication with the LDAP server for the dn %dn and saved password succeeded.', array('%dn' => $bind_info['dn'])));
        }
      }
      else {
        drupal_set_message(t('Cannot load server settings. Please save configuration first.'), 'error');
      }
      break;
  }
}


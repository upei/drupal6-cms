<?php
// $Id: ldapgroups.admin.inc,v 1.1.2.9 2008/10/12 19:22:29 miglius Exp $

/**
 * @file
 * Module admin page callbacks.
 */

//////////////////////////////////////////////////////////////////////////////
// ldapgroups settings

/**
 * Implements the LDAP servers list.
 *
 * @return
 *   The HTML table with the servers list.
 */
function ldapgroups_admin_list() {
  $rows = array();
  $result = db_query("SELECT sid, name FROM {ldapauth} WHERE status = '1' ORDER BY name");
  while ($row = db_fetch_object($result)) {
    $rows[] = array(
      $row->name,
      l(t('edit'), 'admin/settings/ldap/ldapgroups/edit/'. $row->sid),
      l(t('reset'), 'admin/settings/ldap/ldapgroups/reset/'. $row->sid),
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

function ldapgroups_admin_edit(&$form_state, $op, $sid) {
  if (($op == 'reset') && $sid) {
    $form['sid'] = array(
      '#type' => 'value',
      '#value' => $sid,
      );
    return confirm_form(
      $form,
      t('Are you sure you want to reset the groups mapping to defaults ?'),
      'admin/settings/ldap/ldapgroups',
      t('<em>This action cannot be undone.</p>'),
      t('Reset'),
      t('Cancel')
    );
  }
  elseif ($op == 'edit' && $sid) {
    $edit = db_fetch_array(db_query("SELECT ldapgroups_in_dn, ldapgroups_dn_attribute, ldapgroups_in_attr, ldapgroups_attr, ldapgroups_as_entries, ldapgroups_entries, ldapgroups_entries_attribute FROM {ldapauth} WHERE sid = %d", $sid));

    $form['group_dn'] = array(
      '#type' => 'fieldset',
      '#title' => t('Group by DN'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
    $form['group_dn']['ldapgroups_in_dn'] = array(
      '#type' => 'checkbox',
      '#title' => t('Group is specified in user\'s DN'),
      '#default_value' => $edit['ldapgroups_in_dn'],
      '#description' => '<p>Check this option if your users\' DNs look like <em style="font-style: normal; padding: 1px 3px; border: 1px solid #8888CC; background-color: #DDDDFF">cn=jdoe,<strong>ou=Group1</strong>,cn=example,cn=com</em> and <em style="font-style: normal; padding: 1px 3px; border: 1px solid #8888CC; background-color: #DDDDFF">Group1</em> turns out to be the group you want.</p>'
    );
    $form['group_dn']['ldapgroups_dn_attribute'] = array(
      '#type' => 'textfield',
      '#title' => t('Attribute of the DN which contains the group name'),
      '#default_value' => $edit['ldapgroups_dn_attribute'],
      '#size' => 50,
      '#maxlength' => 255,
      '#description' => t('The name of the attribute which contains the group name. In the example above, it would be <em style="font-style: normal; padding: 1px 3px; border: 1px solid #8888CC; background-color: #DDDDFF">ou</em>, as the DN contains the string <em style="font-style: normal; padding: 1px 3px; border: 1px solid #8888CC; background-color: #DDDDFF">ou=Group1</em> and <em style="font-style: normal; padding: 1px 3px; border: 1px solid #8888CC; background-color: #DDDDFF">Group1</em> happens to be the desired group name.'),
    );

    $form['group_attr'] = array(
      '#type' => 'fieldset',
      '#title' => t('Group by attribute'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
    $form['group_attr']['ldapgroups_in_attr'] = array(
      '#type' => 'checkbox',
      '#title' => t('Groups are specified by LDAP attributes'),
      '#default_value' => $edit['ldapgroups_in_attr'],
    );
    $form['group_attr']['ldapgroups_attr'] = array(
      '#type' => 'textarea',
      '#title' => t('Attribute names (one per line)'),
      '#default_value' => $edit['ldapgroups_attr'],
      '#cols' => 50,
      '#rows' => 6,
      '#description' => t('If the groups are stored in the user entries, along with the rest of their data, then enter here a list of attributes which may contain them.'),
    );

    $form['group_entry'] = array(
      '#type' => 'fieldset',
      '#title' => t('Group by entry'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
    $form['group_entry']['ldapgroups_as_entries'] = array(
      '#type' => 'checkbox',
      '#title' => t('Groups exist as LDAP entries where a multivalued attribute contains the members\' CNs'),
      '#default_value' => $edit['ldapgroups_as_entries'],
    );
    $form['group_entry']['ldapgroups_entries'] = array(
      '#type' => 'textarea',
      '#title' => t('Nodes containing groups (one per line)'),
      '#default_value' => $edit['ldapgroups_entries'],
      '#cols' => 50,
      '#rows' => 6,
      '#description' => t('Enter here a list of nodes from where groups should be searched for. The module will look them up recursively from the given nodes.'),
    );
    $form['group_entry']['ldapgroups_entries_attribute'] = array(
      '#type' => 'textfield',
      '#title' => t('Attribute holding group members'),
      '#default_value' => $edit['ldapgroups_entries_attribute'],
      '#size' => 50,
      '#maxlength' => 255,
      '#description' => t('Name of the multivalued attribute which holds the CNs of group members, for example: !attr', array('!attr' => theme('placeholder', LDAPGROUPS_DEFAULT_ENTRIES_ATTRIBUTE))),
    );

    $form['sid'] = array(
      '#type' => 'hidden',
      '#value' => $sid,
    );

    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Update'),
    );

    return $form;
  }
  else {
    drupal_goto('admin/settings/ldap/ldapgroups');
  }
}

/**
 * Submit hook for the settings form.
 */
function ldapgroups_admin_edit_submit($form, &$form_state) {
  $op = $form_state['clicked_button']['#value'];
  $values = $form_state['values'];
  switch ($op) {
    case t('Update'):

      // Update the ldapgroups configuration.
      db_query("UPDATE {ldapauth} SET ldapgroups_in_dn = %d, ldapgroups_dn_attribute = '%s', ldapgroups_in_attr = %d, ldapgroups_attr = '%s', ldapgroups_as_entries = %d, ldapgroups_entries = '%s', ldapgroups_entries_attribute = '%s' WHERE sid = %d", $values['ldapgroups_in_dn'], $values['ldapgroups_dn_attribute'], $values['ldapgroups_in_attr'], $values['ldapgroups_attr'], $values['ldapgroups_as_entries'], $values['ldapgroups_entries'], $values['ldapgroups_entries_attribute'], $values['sid']);
      drupal_set_message(t('The configuration options have been saved.'));
      $form_state['redirect'] = 'admin/settings/ldap/ldapgroups';
      break;
    case t('Reset'):
      if ($values['confirm'] == 1) {

        // Settings reset.
        db_query("UPDATE {ldapauth} SET ldapgroups_in_dn = 0, ldapgroups_dn_attribute = '', ldapgroups_in_attr = 0, ldapgroups_attr = '', ldapgroups_as_entries = 0, ldapgroups_entries = '', ldapgroups_entries_attribute = '' WHERE sid = %d", $values['sid']);
        drupal_set_message(t('The configuration options have been reset to their default values.'));
      }
      $form_state['redirect'] = 'admin/settings/ldap/ldapgroups';
      break;
  }
}


<?php
// $Id: clone.pages.inc,v 1.3 2008/05/07 02:28:58 pwolanin Exp $
// $Name: DRUPAL-6--1-0 $

/**
 * Menu callback to configure module settings.
 */
function clone_settings() {

  $form['basic'] = array(
    '#type' => 'fieldset',
    '#title' => t('General settings'),
  );
  $form['basic']['clone_method'] = array(
    '#type' => 'radios',
    '#title' => t('Method to use when cloning a node'),
    '#options' => array('prepopulate' => t('Pre-populate the node form fields'), 'save-edit' => t('Save as a new node then edit')),
    '#default_value' => variable_get('clone_method', 'prepopulate'),
  );
  $form['basic']['clone_nodes_without_confirm'] = array(
    '#type' => 'radios',
    '#title' => t('Confirmation mode when using the "Save as a new node then edit" method'),
    '#default_value' => (int)variable_get('clone_nodes_without_confirm', 0),
    '#options' => array(t('Require confirmation (recommended)'), t('Bypass confirmation')),
    '#description' => t('A new node may be saved immediately upon clicking the "clone" tab when viewing a node, bypassing the normal confirmation form.'),
  );
  
  $form['publishing'] = array(
    '#type' => 'fieldset',
    '#title' => t('Should the publishing options ( e.g. published, promoted, etc) be reset to the defaults?'),
  );
  $types = node_get_types('names');

  foreach ($types as $type => $name) {
    $form['publishing']['clone_reset_'. $type] = array(
      '#type' => 'checkbox',
      '#title' => t('@s: reset publishing options when cloned', array('@s' => $name)),
      '#default_value' => variable_get('clone_reset_'. $type, FALSE),
    );
  }
  // Need the variable default key to be something that's never a valid node type.
  $form['omit'] = array(
    '#type' => 'fieldset',
    '#title' => t('Content types that are not to be cloned - omitted due to incompatibility'),
  );
  $form['omit']['clone_omitted'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Omitted content types'),
    '#default_value' => variable_get('clone_omitted', array()),
    '#options' => $types,
    '#description' => t('Select any node types which should <em>never</em> be cloned. Typically you should will want to select here all node types for which cloning fails (e.g. image nodes).'),
  );

  return system_settings_form($form);
}

/**
 *  Menu callback: prompt the user to confirm the operation
 */
function clone_node_check($node) {

  $method = variable_get('clone_method', 'prepopulate');
  
  switch ($method) {
    case 'save-edit':
      if (variable_get('clone_nodes_without_confirm', FALSE)) {
        $new_nid = clone_node_save($node->nid);
        drupal_goto('node/'. $new_nid .'/edit');
      }
      else {
        return drupal_get_form('clone_node_confirm', $node);
      }
      break;
    case 'prepopulate':
    default:
      include_once(drupal_get_path('module', 'node') .'/node.pages.inc');
      return clone_node_prepopulate($node);
      break;
  }
}

/**
 *  form builder: prompt the user to confirm the operation
 */
function clone_node_confirm($form_state, $node) {

    $form['nid'] = array('#type' => 'value', '#value' => $node->nid);
    return confirm_form($form,
      t('Are you sure you want to clone %title?', array('%title' =>  $node->title)),
      'node/'. $node->nid, '<p>'. t('This action will create a new node. You willl then be redirected to the edit page for the new node.') .'</p>',
      t('Clone'), t('Cancel'));
}

/**
 *  Handle confirm form submission
 */
function clone_node_confirm_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    $new_nid = clone_node_save($form_state['values']['nid']);
  }
  $form_state['redirect'] = 'node/'. $new_nid .'/edit';
}


/**
 *  Clones a node - prepopulate a node editing form
 */
function clone_node_prepopulate($original_node) {
  if (isset($original_node->nid)) {
    global $user;

    if (clone_is_permitted($original_node->type)) {
      $node = drupal_clone($original_node);

      $node->nid = NULL;
      $node->vid = NULL;
      $node->name = $user->name;
      $node->uid = $user->uid;
      $node->created = NULL;
      $node->menu = NULL;
      if (isset($node->book['mlid'])) {
        $node->book['mlid'] = NULL;
      }
      $node->path = NULL;
      $node->files = array();
      $node->title = t('Clone of !title', array('!title' => $node->title));
      drupal_set_title(check_plain($node->title));

      if (variable_get('clone_reset_'. $node->type, FALSE)) {
        $node_options = variable_get('node_options_'. $node->type, array('status', 'promote'));
        // Fill in the default values.
        foreach (array('status', 'moderate', 'promote', 'sticky', 'revision') as $key) {
          $node->$key = in_array($key, $node_options);
        }
      }
      // Let other modules do special fixing up.
      // The function signature is: hook_clone_node_alter(&$node, $original_node, $method)
      // Where $method is either 'prepopulate' or 'save-edit'.
      drupal_alter("clone_node", $node, $original_node, "prepopulate");

      return drupal_get_form($node->type .'_node_form', $node);
    }
  }
}

/**
 *  Clones a node by directly saving it.
 */
function clone_node_save($nid) {
  if (is_numeric($nid)) {
    global $user;

    $node = node_load($nid);
    if (isset($node->nid) && clone_is_permitted($node->type)) {
      $original_node = drupal_clone($node);

      $node->nid = NULL;
      $node->vid = NULL;
      $node->name = $user->name;
      $node->uid = $user->uid;
      $node->created = NULL;
      $node->menu = NULL;
      $node->book['mlid'] = NULL;
      $node->path = NULL;
      $node->files = array();
      $node->title = t('Clone of !title', array('!title' => $node->title));

      if (variable_get('clone_reset_'. $node->type, FALSE)) {
        $node_options = variable_get('node_options_'. $node->type, array('status', 'promote'));
        // Fill in the default values.
        foreach (array('status', 'moderate', 'promote', 'sticky', 'revision') as $key) {
          $node->$key = in_array($key, $node_options);
        }
      }
      // Let other modules do special fixing up.
      // The function signature is: hook_clone_node_alter(&$node, $original_node, $method)
      // Where $method is either 'prepopulate' or 'save-edit'.
      drupal_alter("clone_node", $node, $original_node, "save-edit");

      node_save($node);
      return $node->nid;
    }
  }
}


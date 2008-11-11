<?php
// $Id: ldapgroups.conf.php,v 1.9.2.3 2008/08/11 11:12:36 miglius Exp $

/**
 * @file
 * ldapgroups module configuration options.
 */

/**
 * Interesting constants that admins would want to mess with.
 *
 * The module automatically decides names for the Drupal roles
 * based in the names of the LDAP groups. For example:
 * - LDAP group: Admins => Drupal role: Admins
 * - LDAP group: ou=Underlings,dc=myorg,dc=mytld => Drupal role: Underlings
 * However, if this is not enough, this name mapping can be refined
 * by altering this array. Some examples are given.
 */
function ldapgroups_role_mappings() {
  return array(
    // LDAP group => Drupal role

    // Make sure the last group->role mapping does NOT have a trailing comma (,).
    //'cn=admin,ou=Group,dc=example,dc=com' => 'IT'
  );
}

/**
 * Note: Uncommenting this function will limit the groups -> roles conversion to ONLY those groups that are
 * specified in the function ldapgroups_role_mappings().
 */
/*
function ldapgroups_roles_filter($groups) {
  $roles = array();
  // This should take the roles array, pass it thru the filters and send a NEW set of roles back the filter.
  foreach ($groups as $group) {
    foreach (ldapgroups_role_mappings() as $approved_group => $approved_role) {
      // Must strip spaces?
      $group_stripped = preg_replace('/\s+/', '', $group);
      $approved_group_stripped = preg_replace('/\s+/', '', $approved_group);
      if (strcasecmp($approved_group_stripped, $group_stripped) == 0) {
        // This role is specified - grant.
        $roles[] = $approved_role;
      }
    }
  }
  return $roles;
}
 */


<?php
// $Id: phone.fr.inc,v 1.23 2009/03/08 00:04:26 thierrygd Exp $

/**
 * @file
 * CCK Field for French phone numbers.
 */

define('PHONE_FR_REGEX', "/(\+33|0)([1-6]\d{8}|85\d{7}|87[0-57-9]\d{6})$/");

/**  
 * Verification for French Phone Numbers.  
 * According to http://www.itu.int/itudoc/itu-t/number/f/fra/70680.html
 *    (Released 2006/01/26, retrieved 2008/08/12) 
 *
 * @param string $phonenumber
 * @return boolean Returns boolean FALSE if the phone number is not valid. 
 */
function valid_fr_phone_number($phonenumber) {

  //$phonenumber = trim($phonenumber);

  $phonenumber  = str_replace(array(' ','-','(',')'), '', $phonenumber);
  return (bool) preg_match(PHONE_FR_REGEX, $phonenumber);
}

/**
 * Formatting for French Phone Numbers.  
 *
 * @param string $phonenumber
 * @return string Returns a string containting the phone number with some formatting.
 */
function format_fr_phone_number($phonenumber, $field = FALSE) {
  $phone  = str_replace(array(' ','-','(',')'), '', $phonenumber);
  if (preg_match(PHONE_FR_REGEX, $phone, $matches) != 1) {
    return $phonenumber; // not a french phone number
  }

  return ($field && $field['phone_country_code'] ? '+33 ' : '0') . $matches[2];
}

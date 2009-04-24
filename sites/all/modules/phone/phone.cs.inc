<?php
// $Id: phone.cs.inc,v 1.14 2009/03/08 00:04:26 thierrygd Exp $

/**
 * @file
 * CCK Field for Czech phone numbers.
 */
 
/**  
 * Verifies that $phonenumber is a valid nine-digit Czech phone number
 *
 * @param string $phonenumber
 * @return boolean Returns boolean FALSE if the phone number is not valid. 
 */
function valid_cs_phone_number($phonenumber) {

  $phonenumber = trim($phonenumber);

  // define regular expression
  $regex = "/^((\+|00)420)?( ?\d{3}){3}$/";

  // return true if valid, false otherwise
  return (bool) preg_match($regex, $phonenumber);
} 

/**
 * Convert a valid Czech phone number into standard (+420) 999 999 999 format
 * 
 * @param $phonenumber must be a valid nine-digit number (with optional international prefix)
 * 
 */
function format_cs_phone_number($phonenumber) {

  // define regular expression   
  $regex = "/^((\+|00)420)? ?(\d{3}) ?(\d{3}) ?(\d{3})$/";

  // get digits of phone number
  preg_match($regex, $phonenumber, $matches);
  
  if ($field['phone_country_code']) {
        if ($matches[1] != "+420") {
    	$phonenumber = "+420" . " " . $matches[3] .' '. $matches[4] .' '. $matches[5]; 
        }
   }   
  else { 
  	$phonenumber = $matches[3] .' '. $matches[4] .' '. $matches[5];
  }
 
  return $phonenumber;
}
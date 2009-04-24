<?php
// $Id: phone.ca.inc,v 1.25 2009/03/08 00:04:26 thierrygd Exp $

/**
 * @file
 * CCK Field for Canadian phone numbers.
 */
 
/**  
 * Verifies that $phonenumber is a valid ten-digit North American phone number
 *
 * @param string $phonenumber
 * @return boolean Returns boolean FALSE if the phone number is not valid. 
 */

function valid_ca_phone_number($phonenumber) {

  //$phonenumber = trim($phonenumber);

  // define regular expression
  $regex = "/
    \D*           # ignore non-digits
    1?            # an optional 1
    \D*           # optional separator 
    [02-9]\d{2}   # area code (can't start with 1)
    \D*           # optional separator
    [02-9]\d{2}   # 3-digit prefix (can't start with 1)    
    \D*           # optional separator
    \d{4}         # 4-digit line number
    \D*           # optional separator
    \d*           # optional extension
    \D*           # ignore trailing non-digits
    /x";
  // return true if valid, false otherwise
  return (bool) preg_match($regex, $phonenumber); 
} 

/**
 * Convert a valid North American phone number into standard (444) 867-5309 x1234 format
 * 
 * @param $phonenumber must be a valid ten-digit number (with optional extension)
 * 
 */
function format_ca_phone_number($phonenumber, $field) {

  // define regular expression   
  $regex = "/
    ^\D*          # ignore non-digits
    1?            # an optional 1
    \D*           # optional separator 
    ([02-9]\d{2}) # capture area code       
    \D*           # optional separator
    (\d{3})       # capture 3-digit prefix
    \D*           # optional separator
    (\d{4})       # capture 4-digit line number                       
    \D*           # optional separator
    (\d*)         # capture optional extension                       
    \D*$          # ignore trailing non-digits
  /x"; 
    
  // get digits of phone number
  preg_match($regex, $phonenumber, $matches);
  
  $separator = isset($field['ca_phone_separator']) ? $field['ca_phone_separator'] : '-';
  
  // construct ten-digit phone number
  $phonenumber =
    ( $field['ca_phone_parentheses'] ?
      '(' . $matches[1] . ') ' :
      $matches[1] . $separator ) .
      $matches[2] . $separator . $matches[3];  

 // Optional extension
  if ($matches[4] != '') {
      $phonenumber .= ' x' . $matches[4];
  }
  
  if ($field['phone_country_code']) {
    if ($matches[1] != "1") {
  	$phonenumber = "1" . " " . $phonenumber; 
    }
  }

  return $phonenumber;
}

<?php
// $Id: phone.es.inc,v 1.17 2008/12/08 01:26:54 thierrygd Exp $

/**
 * @file
 * CCK Field for Spanish phone numbers.
 */
 
/**  
 * Verifies that $phonenumber is a valid nine-digit Spanish phone number
 *
 * @param string $phonenumber
 * @return boolean Returns boolean FALSE if the phone number is not valid. 
 */
function valid_es_phone_number($phonenumber) {

  //$phonenumber = trim($phonenumber);

  // define regular expression
  $regex = "/
    \D*           # optional separator 
    [69]\d{2}     # first group of numbers
    \D*           # optional separator
    \d{3}         # second group
    \D*           # optional separator
    \d{3}         # third group
    \D*           # ignore trailing non-digits
    $/x";
  // return true if valid, false otherwise
  return (bool) preg_match($regex, $phonenumber); 
} 

/**
 * Convert a valid Spanish phone number into standard (+34) 916 555 777 format
 * 
 * @param $phonenumber must be a valid nine-digit number (with optional international prefix)
 * 
 */
function format_es_phone_number($phonenumber) {

  // define regular expression   
  $regex = "/
    \D*           # optional separator 
    ([69]\d{2})   # first group of numbers
    \D*           # optional separator
    (\d{3})       # second group
    \D*           # optional separator
    (\d{3})       # third group
    \D*           # ignore trailing non-digits
    $/x"; 
    
  // get digits of phone number
  preg_match($regex, $phonenumber, $matches);
  
  // construct ten-digit phone number
  $phonenumber = $matches[1] . ' ' . $matches[2] . ' ' . $matches[3];
  
  return $phonenumber;
}


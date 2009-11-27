<?php

// $Id: phone.jo.inc,v 1.2 2009/11/05 11:07:56 thierrygd Exp $

/**
 * @file
 * CCK Field for Jordanian cellular phone numbers.
 */
 
function phone_jo_metadata(){
  // These strings are translated using t() on output.
  return array(
    'value' => 'Jordanian Mobile Phone Numbers',
    'error' => '"%value" is not a valid Jordanian mobile phone number',
  );
}

/**  
 * Verification for Jordanian Mobile Phone Numbers.  
 *
 * @param string $phonenumber
 * @return boolean Returns boolean FALSE if the phone number is not valid. 
 */
function valid_jo_phone_number($phonenumber){
  
  /** Accepts:
    079xxxxxxx or 79xxxxxxx (Zain)
    077xxxxxxx or 77xxxxxxx (Orange)
    078xxxxxxx or 78xxxxxxx (Umniah)
  **/
  $regex = "/[0]{0,1}[7]{1}[7-9]{1}[0-9]{7}$/x";

  return (bool) preg_match($regex, $phonenumber);
}

/**
 * Formatting for Jordanian Mobile Phone Numbers.  
 *
 * @param string $phonenumber
 * @return string Returns a string containting the phone number with some formatting.
 */
function format_jo_phone_number($phonenumber){

  $regex = "/[0]{0,1}[7]{1}[7-9]{1}[0-9]{7}$/x";
  preg_match($regex, $phonenumber, $matches);
  
  $phonenumber = preg_replace('/^0/', '', $matches[0]);

  return $phonenumber;

}

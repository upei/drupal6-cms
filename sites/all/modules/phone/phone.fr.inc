<?php
// $Id: phone.fr.inc,v 1.22 2008/12/08 01:26:54 thierrygd Exp $

/**
 * @file
 * CCK Field for French phone numbers.
 */
 
/**  
 * Verification for French Phone Numbers.  
 *
 * @param string $phonenumber
 * @return boolean Returns boolean FALSE if the phone number is not valid. 
 */
function valid_fr_phone_number($phonenumber) {

  //$phonenumber = trim($phonenumber);

  if (!preg_match("/^(\+){0,1}([0-9 ])*[0-9]$/i",$phonenumber)) { 
  	return FALSE; 
  }
  //right now just do a quick check ==> has to be improved 
  //need to count how many numbers have been filled, ...
  else 
  {
	return TRUE;
  }
}  

/**
 * Formatting for French Phone Numbers.  
 *
 * @param string $phonenumber
 * @return string Returns a string containting the phone number with some formatting.
 */
function format_fr_phone_number($phonenumber, $field) {

  //$phonenumber = trim($phonenumber);

   // do some formatting on the phone number 
   //if doesn't start by '+' add it at the beginning and ins not empty
  if (!preg_match("/^(\+){1}[0-9 ]*$/i",$phonenumber) && !$phonenumber == '') 
  {
	$phonenumber = '+' . $phonenumber;
  }
    
  if ($field['phone_country_code']) {
        //if french phone number, add the country code at the beginning 
        if (!preg_match("/^(\+){1}33[ ]*[0-9 ]*$/i",$phonenumber) && !$phonenumber == '') 
        {
	     $phonenumber = str_replace("+", "+" . "33" . " ", $phonenumber);
        }
  }
  return $phonenumber;
}
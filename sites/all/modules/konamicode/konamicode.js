/* $Id: konamicode.js,v 1.1 2009/05/11 14:25:32 robloach Exp $ */

/**
 * @file
 * Redirects the user to a page when they enter the Konami Code.
 */

/**
 * The Drupal behavior to redirect the user when they enter the Konami Code.
 *
 * Thank you to jQuery.com and John Resig for the Konami Code event listener.
 */
Drupal.behaviors.konamicode = function() {
  if (window.addEventListener) {
    var kkeys = [], konami = "38,38,40,40,37,39,37,39,66,65";
    window.addEventListener("keydown", function(e){
      kkeys.push(e.keyCode);
      if (kkeys.toString().indexOf(konami) >= 0) {
        window.location = Drupal.settings.konamicode;
      }
    }, true);
  }
}

// $Id: layout.js,v 1.2 2008/07/16 00:09:04 merlinofchaos Exp $
/**
 * @file layout.js 
 *
 * Contains javascript to make layout modification a little nicer.
 */

Drupal.Panels.Layout = {};
Drupal.Panels.Layout.autoAttach = function() {
  $('div.form-item div.layout-icon').click(function() {
    $(this).prev().find('input').attr('checked', true);
  });
};

$(Drupal.Panels.Layout.autoAttach);

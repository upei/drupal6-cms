// $Id: tableofcontents.js,v 1.1.2.1.2.2 2008/06/21 18:11:12 deviantintegral Exp $

if (Drupal.jsEnabled) {
  $(document).ready( function () {
    $('a.toc-toggle').click(function() {
      $('.toc-list').slideToggle();
	  var text = $('a.toc-toggle').text();
	  if (text == Drupal.t('hide')) {
		  $('a.toc-toggle').text(Drupal.t('show'));
      } else {
		  $('a.toc-toggle').text(Drupal.t('hide'));
      }
	  return false;
	});
  });
}
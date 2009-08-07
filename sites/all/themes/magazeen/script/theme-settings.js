// $Id: theme-settings.js,v 1.1.2.2 2009/05/04 17:12:02 zinv Exp $
$(document).ready( function() {
  // Hide the breadcrumb details, if no breadcrumb.
  $('#edit-breadcrumb-display').change(
    function() {
      div = $('#div-breadcrumb-collapse');
      if ($('#edit-breadcrumb-display').val() == 'no') {
        div.slideUp('fast');
      } else if (div.css('display') == 'none') {
        div.slideDown('fast');
      }
    }
  );
  if ($('#edit-breadcrumb-display').val() == 'no') {
    $('#div-breadcrumb-collapse').css('display', 'none');
  }
  $('#edit-breadcrumb-display-title').change(
    function() {
      checkbox = $('#edit-breadcrumb-display-trailing');
      if ($('#edit-breadcrumb-display-title').attr('checked')) {
        checkbox.attr('disabled', 'disabled');
      } else {
        checkbox.removeAttr('disabled');
      }
    }
  );
  $('#edit-breadcrumb-display-title').change();
} );

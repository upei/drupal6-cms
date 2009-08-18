Drupal.behaviors.searchRanking = function() {
  // Catch the enter keypress in the sample search input so that the whole form is not submitted.
  $('#edit-sample-search').keypress(function(e) {
    if (e.which == 13) {
      return false;
    }
  });
  
  // Catch a change in ranking score settings and display a notice to save the form.
  $('#search_ranking select').change(function() {
    if (!$(this).parents('tr.drag-previous').size()) {
      $(this).parents('tr').addClass('drag-previous').children('td:first').append('<span class="warning">*</span>');
    }
    $('#search_ranking_notice').show();
  });
  
};
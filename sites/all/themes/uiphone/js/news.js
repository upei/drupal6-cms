var NewsManager = function(endpoint) {
  this.endpoint = endpoint;
}

NewsManager.prototype = {}
NewsManager.prototype.load = function(container) {
  var ctr = jQuery(container);
  jQuery.ajax({
    type: 'GET',
    dataType: 'json',
    url: this.endpoint,
    success: function(data, status) {
      var rows = data[0].rows;
      if (rows.length > 0) {
        var html = '';
        for (var i=0; i<rows.length; i++) {
          var row = rows[i];
          html += '<div class="rounded">\n';
          html += '<h3>' + row.title + '</h3>\n';
          html += '<div class="date">' + row.timestamp + '</div>\n';
          html += row.body + '\n';
          html += '</div>\n';
        }
      }
      else {
        html = Drupal.t('<div class="rounded">Sorry, no result is found.</div>');
      }
      ctr.html(html);
    },
    error: function(request, status, err) {
      ctr.html(Drupal.t('Sorry, an error occurs.') + '<br/>' + status + err);
    }
  });
}
EmergencyManager = function (endpoint) {
  this.endpoint = endpoint;
}

EmergencyManager.prototype.replace = function(target) {
  jQuery.ajax({
    type: 'GET',
    url: this.endpoint,
    dataType: 'json',
    success: function(data, status) {
      if (data['in-emergency']) {
        $(target).html(data.messages[0].body);
        $(target).find('*:empty').remove().end().find('*').filter(function() {
          return $(this).text().replace(/\s+/, '') == '';
        }).remove();
      }
      else {
        $(target).text('There is currently no emergency.');
      }
    },
    error: function(request, status, err) {
      $(target).html('An error occurs when retrieving emergency information.<br/>' + status);
    }
  });
}

var PeopleManager = function(container, apis) {
  this.container = container;
  this.searchAPI = apis.search;
  this.detailAPI = apis.detail;
  this.q = jQuery.parseQuery();
}

PeopleManager.prototype = {
  search: function() {
    var ctr = $(this.container);
    var loc = this;
    $.ajax({
      type: 'GET',
      dataType: 'json',
      url: this.searchAPI + (this.q.keys ? this.q.keys : ''),
      success: function(data, status) {
        data = data[0];
        var rows = data.rows;
        if (rows.length > 0) {
          // check if we have only one result
          if (rows.length == 1) {
            // document.location.href = Drupal.settings.basePath + 'people/detail?email=' + rows[0].Email;
          }
          var html = '<ul class="results">';
          for (var i = 0; i < rows.length; i++) {
            var row = rows[i];
            html += '<li><a href="' + Drupal.settings.basePath + 'people/detail?email=' + row.Email + '">';
            html += row.Name;
            html += '</a></li>';
          }
          html += '</ul>';
        }
        else {
          html = Drupal.t('<div class="rounded">Sorry, no result is found.</div>');
        }
        ctr.html(html);
      },
      error: function(request, status, err) {
      }
    });
  },
  detail: function() {
    var ctr = $(this.container);
    var loc = this;
    $.ajax({
      type: 'GET',
      dataType: 'json',
      url: this.detailAPI + (this.q.email ? this.q.email : ''),
      success: function(data, status) {
        data = data[0];
        var rows = data.rows;
        if (rows.length > 0) {
          var row = rows[0];
          var tabs = {
            'Info': function() {
              html = '<div class="description"><dl>';
              html += '<dt>name</dt>';
              html += '<dd>' + row.Name + '</dd>';
              html += '<dt>department</dt>';
              html += '<dd>' + row.Department + '</dd>';
              html += '<dt>location</dt>';
              // html += '<dd><a href="' + Drupal.settings.basePath + 'location/detail?name=' + row.Building + '">' + row.Building + ' ' + row.Room + '</a></dd>';
              html += '<dd>' + row.Building + ' ' + row.Room + '</dd>';
              html += '<dt>tel</dt>';
              if (row.Phone.match(/^(566|620|894)/)) {
                row.Phone = '(902)'+row.Phone;
              }
              html += '<dd><a href="tel:' + row.Phone + '">' + row.Phone + '</a></dd>';
              html += '<dt>email</dt>';
              html += '<dd><a href="mailto:' + row.Email + '">' + row.Email + '</a></dd>';
              html += '</dl><div style="clear:both;"></div></div>';
              return html;
            }
          };
          var bar = '<ul class="tabs">';
          var cont = '<div class="detail">';
          var index = 0;
          for (tab in tabs) {
            bar += '<li><a href="#tab-' + index + '">' + tab + '</a></li>\n';
            cont += '<div id="tab-' + index + '">' + tabs[tab]() + '</div>\n';
            index = index + 1;
          }
          bar += '</ul>\n';
          cont += '</div>\n';
          ctr.html(bar + cont);
        }
        else {
          html = Drupal.t('<div class="rounded">Sorry, no result is found.</div>');
        }
      },
      error: function(request, status, err) {
        ctr.html(Drupal.t('Sorry, an error occurs.') + '<br/>' + status + err);
      }
    });
  }
}


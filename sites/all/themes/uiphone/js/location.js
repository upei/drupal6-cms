var LocationManager = function(container, apis) {
  this.searchAPI = apis.search;
  this.detailAPI = apis.detail;
  this.container = container;
  this.q = jQuery.parseQuery();
}

LocationManager.prototype = upei.MapManager
LocationManager.distance = function(lat1, lon1, lat2, lon2) {
  // convert degree into radian
  lat1 = lat1 * Math.PI / 180;
  lat2 = lat2 * Math.PI / 180;
  lon1 = lon1 * Math.PI / 180;
  lon2 = lon2 * Math.PI / 180;
  var R = 6371; // km radius of earth
  var dLat = lat2-lat1;
  var dLon = lon2-lon1; 
  var a = Math.sin(dLat/2) * Math.sin(dLat/2) +
          Math.cos(lat1) * Math.cos(lat2) * 
          Math.sin(dLon/2) * Math.sin(dLon/2); 
  var c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1-a)); 
  var d = R * c;
  return d;
}

LocationManager.prototype.sort = function (rows) {
  if (this.latitude && this.longitude) {
    // caculate all distance
    for (var index = 0; index < rows.length; index ++) {
      rows[index].distance = LocationManager.distance(
        this.latitude, this.longitude,
        rows[index].latitude, rows[index].longitude
        );
    }
    // sort by distance
    rows.sort(function(a, b) {
      return a.distance - b.distance;
    });
    return rows;
  }
  else {
    return rows;
  }
}


LocationManager.prototype.search = function() {
  var ctr = jQuery(this.container);
  var loc = this;
  jQuery.ajax({
    'type': 'GET',
    'dataType': 'json',
    'url': this.searchAPI + (this.q.keys ? this.q.keys : ''),
    'success': function(data, status) {
      data = data[0];
      // list all rows
      var rows = loc.sort(data.rows);
      if (rows.length > 0) {
        // redirect if we have only one result
        if (rows.length == 1) {
          // document.location.href = Drupal.settings.basePath + 'location/detail?nid=' + rows[0].nid;
        }
        var html = '<ul class="results">';
        for (var i=0; i<rows.length; i++) {
          var row = rows[i];
          if (row.distance) {
            dist = '<span class="note">&lt;' + (row.distance > 1 ? (Math.ceil(row.distance) + 'k') : (Math.ceil(row.distance * 1000))) + 'm</span>';
          }
          else {
            dist = '';
          }
          html += '<li>' + dist + '<a href="' + Drupal.settings.basePath + 'location/detail?nid=' + row.nid + '">';
          html += row.title;
          if (row.building_number > 0) {
            html += ' (' + row.building_number + ')';
          }
          html += "</a></li>\n";
        }
        html += '</ul>';
      }
      else {
        html = Drupal.t('<div class="rounded">Sorry, no result is found.</div>');
      }
      ctr.html(html);
    },
    'error': function(request, status, err) {
      ctr.html(Drupal.t('Sorry, an error occurs.') + '<br/>' + status + err);
    }
  });
}

LocationManager.prototype.detail = function() {
  var ctr = jQuery(this.container);
  var loc = this;
  jQuery.ajax({
    'type': 'GET',
    'dataType': 'json',
    'url': this.detailAPI + (this.q.name ? this.q.name + '/' : 'all/' ) + (this.q.nid ? this.q.nid: 'all'),
    'success': function(data, status) {
      data = data[0];
      if (data.rows.length > 0) {
        row = data.rows[0];
        var tabs = {
          'Description': function() {
            var html = '';
            html += '<h2>' + row.title + "</h2>\n";
            html += '<div class="description">';
            if (row.building_number > 0) {
              html += '<p>Building number: ' + row.building_number + '</p>';
            }
            if (row.picture) {
              html += '<p>' + row.picture + '</p>';
            }
            html += row.description + "</div>\n";
            return html;
          },
          'Map': function() {
            var html = '';
            html += '<div id="gmap"></div>';
            return html;
          },
          "What's Here": function() {
            var html = '';
            html += '<div class="description">' + row.occupants + "</div>\n";
            return html;
          }
        };
        var bar = '<ul class="tabs">';
        var cont = '<div class="detail">';
        var index = 0;
        for (var tab in tabs) {
          bar += '<li><a href="#tab-' + index + '">' + tab + "</a></li>\n";
          cont += '<div id="tab-' + index + '">' + tabs[tab]() + "</div>\n";
          index = index + 1;
        }
        bar += "</ul>\n";
        cont += "</div>\n";
        ctr.html(bar + cont);
        // enable map
        loc.map('gmap', row.latitude, row.longitude);
        // click on tab
        ctr.find('.tabs a').click(function() {
          var id = $(this).attr('href');
          $(this)
            .parent()
              .siblings().removeClass('active')
              .end()
            .addClass('active');
          ctr.find(id)
            .siblings().hide()
            .end()
            .show();
          return false;
        });
        ctr.find('.tabs li:first a').click();
      }
    },
    'error': function(request, status, err) {
      ctr.html(Drupal.t('Sorry, an error occurs.') + '<br/>' + status);
    }
  });
}

LocationManager.prototype.map = function(map_id, lat, lon) {
  /*
   * Constants for given map
   * TODO: read it from tilemapresource.xml
   */
  var mapBounds = this.mapBounds();
  var map;
  var centre = mapBounds.getCenter();
  var where;
  if (lat && lon) {
    where = new GLatLng(lat, lon);
  }  
  if (GBrowserIsCompatible()) {
    map = this.create(map_id);
    map.setCenter( where, 16 );
    this.addCampusOverlay(map);
    this.addMarker(map, lat, lon);

    // add where you are
    if (this.latitude && this.longitude) {
     // Create our "tiny" marker icon
     var icon = new GIcon(G_DEFAULT_ICON);
     var pos = new GLatLng(this.latitude, this.longitude);
     icon.image = "http://www.google.com/intl/en_us/mapfiles/ms/micons/yellow-dot.png";
     icon.iconSize = new GSize(32, 32);
     // Set up our GMarkerOptions object
     markerOptions = { icon:icon };
     this.addMarker(map, this.latitude, this.longitude, markerOptions);
     // set up center if we're inside the bound
     if (mapBounds.contains(pos)) {
       var center = new GLatLng((where.lat()+pos.lat())/2, (where.lng()+pos.lng())/2);
       map.setCenter(center, 16);
     }
    }
    // this.addNameOverlay(map);
    map.addControl(new GSmallZoomControl3D());
    map.addControl(new GScaleControl);
    map.disableContinuousZoom();
    map.disableScrollWheelZoom();
    // map.disableDragging();
    map.disableInfoWindow();
    map.setMapType(G_NORMAL_MAP);
  }

}

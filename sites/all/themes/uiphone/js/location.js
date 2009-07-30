var LocationManager = function(container, apis) {
  this.searchAPI = apis.search;
  this.detailAPI = apis.detail;
  this.container = container;
  this.q = jQuery.parseQuery();
}

LocationManager.prototype = {}
LocationManager.prototype.distance = function(lat1, lon1, lat2, lon2) {
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
      rows[index].distance = this.distance(
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
        html = Drupal.t('<p>Sorry, no result is found.</p>');
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
    'url': this.detailAPI + this.q.nid,
    'success': function(data, status) {
      data = data[0];
      row = data.rows[0];
      var tabs = {
        'Map': function() {
          var html = '';
          html += '<div id="gmap"></div>';
          return html;
        },
        "What's Here": function() {
          var html = '';
          html += '<div class="description">' + row.occupants + "</div>\n";
          return html;
        },
        'Description': function() {
          var html = '';
          html += '<h2>' + row.title + "</h2>\n";
          html += '<div class="description">';
          if (row.building_number > 0) {
            html += '<p>Building number: ' + row.building_number + '</p>';
          }
          html += row.description + "</div>\n";
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
  // map bounds
  var mapBounds = new GLatLngBounds(new GLatLng(46.2514795465, -63.144328), new GLatLng(46.262567, -63.1334033165));
  var mapMinZoom = 14;
  var mapMaxZoom = 18;

  var opacity = 0.9;
  var map;
  var centre = mapBounds.getCenter();
  var where;
  if (lat && lon) {
    where = new GLatLng(lat, lon);
  }  
  if (GBrowserIsCompatible()) {

     // Bug in the Google Maps: Copyright for Overlay is not correctly displayed
     // set minimum and maximum level
     G_NORMAL_MAP.getMaximumResolution = function() { return 18; }
     G_NORMAL_MAP.getMinimumResolution = function() { return 10; }
     
     var gcr = GMapType.prototype.getCopyrights;
     GMapType.prototype.getCopyrights = function(bounds,zoom) {
         return ["&copy; 2009 UPEI"].concat(gcr.call(this,bounds,zoom));;
     }

     map = new GMap2( document.getElementById(map_id), { backgroundColor: '#fff' } );

     map.addMapType(G_NORMAL_MAP);
     map.setMapType(G_NORMAL_MAP);

     map.setCenter( where, 16 );

     // tile layer
     var tilelayer = new GTileLayer(GCopyrightCollection(''), mapMinZoom, mapMaxZoom);
     var mercator = new GMercatorProjection(mapMaxZoom+1);
     tilelayer.getTileUrl = function(tile,zoom) {
         if ((zoom < mapMinZoom) || (zoom > mapMaxZoom)) {
             return "http://www.maptiler.org/img/none.png";
         } 
         var ymax = 1 << zoom;
         var y = ymax - tile.y -1;
         var tileBounds = new GLatLngBounds(
             mercator.fromPixelToLatLng( new GPoint( (tile.x)*256, (tile.y+1)*256 ) , zoom ),
             mercator.fromPixelToLatLng( new GPoint( (tile.x+1)*256, (tile.y)*256 ) , zoom )
         );
         if (mapBounds.intersects(tileBounds)) {
             return 'http://www.upei.ca/misc/maps/' + zoom+"/"+tile.x+"/"+y+".png";
         } else {
             return "http://www.maptiler.org/img/none.png";
         }
     }
     
     // marker
     if (lat && lon) {
       map.addOverlay(new GMarker(where));
     }
     // add where you are
     if (this.latitude && this.longitude) {
       // Create our "tiny" marker icon
       var icon = new GIcon(G_DEFAULT_ICON);
       var pos = new GLatLng(this.latitude, this.longitude);
       icon.image = "http://www.google.com/intl/en_us/mapfiles/ms/micons/yellow-dot.png";
       // Set up our GMarkerOptions object
       markerOptions = { icon:icon };
       map.addOverlay(new GMarker(pos, markerOptions));
       // set up center if we're inside the bound
       if (mapBounds.contains(pos)) {
         var center = new GLatLng((where.lat()+pos.lat())/2, (where.lng()+pos.lng())/2);
         map.setCenter(center, 16);
       }
     }
     
     // IE 7-: support for PNG alpha channel
     // Unfortunately, the opacity for whole overlay is then not changeable, either or...
     tilelayer.isPng = function() { return true;};
     tilelayer.getOpacity = function() { return opacity; }

     overlay = new GTileLayerOverlay( tilelayer );
     map.addOverlay(overlay);
     // add road and names overlay
     var hybridOverlay = new GTileLayerOverlay( G_HYBRID_MAP.getTileLayers()[1] );
     map.addOverlay(hybridOverlay);

     map.addControl(new GSmallMapControl());

     map.disableContinuousZoom();
     map.disableScrollWheelZoom();
     // map.disableDragging();
     map.disableInfoWindow();

     map.setMapType(G_NORMAL_MAP);
  }

}
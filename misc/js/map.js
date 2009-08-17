upei = {}
upei.MapManager = {
  version: '0.2',
  create: function(map_id) {
    map = new GMap2( document.getElementById(map_id), { backgroundColor: '#fff' } );

    map.addMapType(G_NORMAL_MAP);
    map.setMapType(G_NORMAL_MAP);
    return map;
  },
  mapBounds: function() {
    return new GLatLngBounds(new GLatLng(46.2514783836, -63.144346), new GLatLng(46.262562, -63.1335834371));
  },
  addCampusOverlay: function(map) {
    /*
     * Constants for given map
     * TODO: read it from tilemapresource.xml
     */
    // map bounds
    var mapBounds = upei.MapManager.mapBounds();
    var mapMinZoom = 14;
    var mapMaxZoom = 18;

    var opacity = 0.9;
    var map;
    var centre = mapBounds.getCenter();
    // tile layer
    var tilelayer = new GTileLayer(GCopyrightCollection(''), mapMinZoom, mapMaxZoom);
    var mercator = new GMercatorProjection(mapMaxZoom+1);
    tilelayer.getTileUrl = function(tile,zoom) {
      if ((zoom < mapMinZoom) || (zoom > mapMaxZoom)) {
          return "http://www.upei.ca/misc/maps/none.png";
      } 
      var ymax = 1 << zoom;
      var y = ymax - tile.y -1;
      var tileBounds = new GLatLngBounds(
          mercator.fromPixelToLatLng( new GPoint( (tile.x)*256, (tile.y+1)*256 ) , zoom ),
          mercator.fromPixelToLatLng( new GPoint( (tile.x+1)*256, (tile.y)*256 ) , zoom )
      );
      if (mapBounds.intersects(tileBounds)) {
          return 'http://www.upei.ca/misc/maps/' + zoom+"/"+tile.x+"/"+y+".png?v=" + upei.MapManager.version;
      } else {
          return "http://www.upei.ca/misc/maps/none.png";
      }
    }
    // IE 7-: support for PNG alpha channel
    // Unfortunately, the opacity for whole overlay is then not changeable, either or...
    tilelayer.isPng = function() { return true;};
    tilelayer.getOpacity = function() { return opacity; }

    overlay = new GTileLayerOverlay( tilelayer );
    map.addOverlay(overlay);
    // set minimum and maximum level
    G_NORMAL_MAP.getMaximumResolution = function() { return 18; }
    G_SATELLITE_MAP.getMaximumResolution = function() { return 18; }
    G_HYBRID_MAP.getMaximumResolution = function() { return 18; }
  },
  addNameOverlay: function(map) {
    // add road and names overlay
    var hybridOverlay = new GTileLayerOverlay( G_HYBRID_MAP.getTileLayers()[1] );
    map.addOverlay(hybridOverlay);
  },
  addMarker: function(map, lat, lon, markerOptions) {
    var where = new GLatLng(lat, lon);
    // marker
    if (lat && lon) {
      map.addOverlay(new GMarker(where, markerOptions));
    }
  }
}

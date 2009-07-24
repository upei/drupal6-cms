/*
 * Create a Custom Opacity GControl
 * http://www.maptiler.org/google-maps-overlay-opacity-control/
 */

var CTransparencyLENGTH = 58; 
// maximum width that the knob can move (slide width minus knob width)

function CTransparencyControl( overlay ) {
  this.overlay = overlay;
  this.opacity = overlay.getTileLayer().getOpacity();
}
CTransparencyControl.prototype = new GControl();

// This function positions the slider to match the specified opacity
CTransparencyControl.prototype.setSlider = function(pos) {
  var left = Math.round((CTransparencyLENGTH*pos));
  this.slide.left = left;
  this.knob.style.left = left+"px";
  this.knob.style.top = "0px";
}

// This function reads the slider and sets the overlay opacity level
CTransparencyControl.prototype.setOpacity = function() {
// set the global variable
  opacity = this.slide.left/CTransparencyLENGTH;
  this.map.clearOverlays();
  this.map.addOverlay(this.overlay, { zPriority: 0 });
  if (this.map.getCurrentMapType() == G_HYBRID_MAP) {
      this.map.addOverlay(hybridOverlay);
  }
}

// This gets called by the API when addControl(new CTransparencyControl())
CTransparencyControl.prototype.initialize = function(map) {
  var that=this;
  this.map = map;

  // Is this MSIE, if so we need to use AlphaImageLoader
  var agent = navigator.userAgent.toLowerCase();
  if ((agent.indexOf("msie") > -1) && (agent.indexOf("opera") < 1)){this.ie = true} else {this.ie = false}

  // create the background graphic as a <div> containing an image
  var container = document.createElement("div");
  container.style.width="70px";
  container.style.height="21px";

  // Handle transparent PNG files in MSIE
  if (this.ie) {
    var loader = "filter:progid:DXImageTransform.Microsoft.AlphaImageLoader(src='http://www.maptiler.org/img/opacity-slider.png', sizingMethod='crop');";
    container.innerHTML = '<div style="height:21px; width:70px; ' +loader+ '" ></div>';
  } else {
    container.innerHTML = '<div style="height:21px; width:70px; background-image: url(http://www.maptiler.org/img/opacity-slider.png)" ></div>';
  }

  // create the knob as a GDraggableObject
  // Handle transparent PNG files in MSIE
  if (this.ie) {
    var loader = "progid:DXImageTransform.Microsoft.AlphaImageLoader(src='http://www.maptiler.org/img/opacity-slider.png', sizingMethod='crop');";
    this.knob = document.createElement("div"); 
    this.knob.style.height="21px";
    this.knob.style.width="13px";
this.knob.style.overflow="hidden";
    this.knob_img = document.createElement("div"); 
    this.knob_img.style.height="21px";
    this.knob_img.style.width="83px";
    this.knob_img.style.filter=loader;
this.knob_img.style.position="relative";
this.knob_img.style.left="-70px";
    this.knob.appendChild(this.knob_img);
  } else {
    this.knob = document.createElement("div"); 
    this.knob.style.height="21px";
    this.knob.style.width="13px";
    this.knob.style.backgroundImage="url(http://www.maptiler.org/img/opacity-slider.png)";
    this.knob.style.backgroundPosition="-70px 0px";
  }
  container.appendChild(this.knob);
  this.slide=new GDraggableObject(this.knob, {container:container});
  this.slide.setDraggableCursor('pointer');
  this.slide.setDraggingCursor('pointer');
  this.container = container;

  // attach the control to the map
  map.getContainer().appendChild(container);

  // init slider
  this.setSlider(this.opacity);

  // Listen for the slider being moved and set the opacity
  GEvent.addListener(this.slide, "dragend", function() {that.setOpacity()});
  //GEvent.addListener(this.container, "click", function( x, y ) { alert(x, y) });

    return container;
}

  // Set the default position for the control
CTransparencyControl.prototype.getDefaultPosition = function() {
  return new GControlPosition(G_ANCHOR_TOP_RIGHT, new GSize(7, 47));
}

/*
 * Main load function:
 */


Drupal.gmap.addHandler('gmap', function(elem) {
  var obj = this;
  var mapBounds = new GLatLngBounds(new GLatLng(46.2514795465, -63.144328), new GLatLng(46.262567, -63.1334033165));
  var mapMinZoom = 14;
  var mapMaxZoom = 18;

  var opacity = 0.75;
  
  obj.bind('init', function() {
    // Bug in the Google Maps: Copyright for Overlay is not correctly displayed
    var gcr = GMapType.prototype.getCopyrights;
    GMapType.prototype.getCopyrights = function(bounds,zoom) {
        return ["&copy; 2009 University of Prince Edward Island"].concat(gcr.call(this,bounds,zoom));
    }

    // obj.map.setCenter( mapBounds.getCenter(), map.getBoundsZoomLevel( mapBounds ));

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
    // IE 7-: support for PNG alpha channel
    // Unfortunately, the opacity for whole overlay is then not changeable, either or...
    tilelayer.isPng = function() { return true;};
    tilelayer.getOpacity = function() { return opacity; }

    overlay = new GTileLayerOverlay( tilelayer );
    obj.map.addOverlay(overlay);
  });
  
});

jQuery.location = new LocationManager(
  '#result-container', {
    'search': '/facilities/map/ajax/json?keys=',
    'detail': '/facilities/building/ajax/json/'
  }
);

// load
$(function() {
  // set current position
  function foundLocation(position) {
    jQuery.location.latitude = position.coords.latitude;
    jQuery.location.longitude = position.coords.longitude;
  }
  function noLocation() {
    jQuery.location.latitude = undefined;
    jQuery.location.longitude = undefined;
  }
  if (navigator.geolocation) {
    navigator.geolocation.getCurrentPosition(foundLocation, noLocation);
  }
  /* skip the address bar */
  setTimeout(function() {
    window.scrollTo(0, 1);
  }, 200);
  /* set search keys */
  var q = $.parseQuery();
  if (q.keys) {
    $('#keys').attr('value', q.keys);
  }
});

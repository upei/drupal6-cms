// load
(function($) {

$.extend($, {
  location: new LocationManager(
    '#result-container', {
      'search': '/facilities/map/ajax/json?keys=',
      'detail': '/facilities/building/ajax/json/'
    }),
  people: new PeopleManager(
    '#result-container', {
      'search': '/staff_faculty/people/search/ajax/json/',
      'detail': '/staff_faculty/people/detail/ajax/json/'
    }),
  emergency: new EmergencyManager(
    '/emergency/cem/endpoint/json'
    ),
  news: new NewsManager(
    '/news/newsfeed/ajax/json/1+2+3+6/all'
    ),
});

$(function() {
  // bind orientationchange
  var updateOrientation = function() {
    setTimeout(function() {window.scrollTo(0, 1)}, 200);
  }
  window.onorientationchange=updateOrientation;

  // set current position
  function foundLocation(position) {
    $.location.latitude = position.coords.latitude;
    $.location.longitude = position.coords.longitude;
  }
  function noLocation() {
    $.location.latitude = undefined;
    $.location.longitude = undefined;
  }
  if (navigator.geolocation) {
    navigator.geolocation.watchPosition(foundLocation, noLocation);
  }
  /* skip the address bar */
  setTimeout(function() {window.scrollTo(0, 1)}, 200);
  /* set search keys */
  var q = $.parseQuery();
  if (q.keys) {
    $('#keys').attr('value', q.keys);
  }
});

})(jQuery);

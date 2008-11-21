(function($) {
Drupal.behaviors.viewscarousel = function(context) {
  $.each(Drupal.settings.viewscarousel, function(id) {
    if (this.scroll) this.scroll = parseInt(this.scroll);
    if (this.start) this.start = parseInt(this.start);
    if (this.visible) this.visible = parseInt(this.visible);
    if (this.auto) this.auto = parseInt(this.auto);
    $('#' + id).jcarousel(this);
  });
}
})(jQuery)
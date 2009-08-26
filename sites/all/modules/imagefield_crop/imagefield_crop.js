/* $Id: imagefield_crop.js,v 1.1.2.3.2.8 2009/06/19 03:49:29 yhager Exp $ */

Drupal.behaviors.imagefield_crop = function (context) { 
  // wait till 'fadeIn' effect ends (defined in filefield_widget.inc)
  setTimeout(attachJcrop, 1000, context);

  function attachJcrop(context) {
    if ($('.cropbox', context).length == 0) {
      // no cropbox, probably an image upload (http://drupal.org/node/366296)
      return;
    }
    var api = $('.cropbox', context).each(function() {
      var self = $(this);
      var src = self.attr('src');
      if (src.indexOf('?') > 0) {
        src = src.substring(0, src.indexOf('?'));
      }
      var widget = self.parent().parent();
      $(this).Jcrop({
        onChange: function(c) {
          var preview = self.parent().parent().parent().find('.widget-preview');
          var rx = Drupal.settings.imagefield_crop.preview[src].width / c.w;
          var ry = Drupal.settings.imagefield_crop.preview[src].height / c.h;
          $('.jcrop-preview', preview).css({
            width: Math.round(rx * Drupal.settings.imagefield_crop.preview[src].orig_width) + 'px',
            height: Math.round(ry * Drupal.settings.imagefield_crop.preview[src].orig_height) + 'px',
            marginLeft: '-' + Math.round(rx * c.x) + 'px',
            marginTop: '-' + Math.round(ry * c.y) + 'px'
          });
        },
        onSelect: function(c) {
            $(".edit-image-crop-x", widget).val(c.x);
            $(".edit-image-crop-y", widget).val(c.y);
            if (c.w) $(".edit-image-crop-width", widget).val(c.w);
            if (c.h) $(".edit-image-crop-height", widget).val(c.h);
            $(".edit-image-crop-changed", widget).val(1);
        },
        aspectRatio: Drupal.settings.imagefield_crop.ratio,
        boxWidth: Drupal.settings.imagefield_crop.box_width,
        boxHeight: Drupal.settings.imagefield_crop.box_height,
        setSelect: [
          parseInt($(".edit-image-crop-x", widget).val()),
          parseInt($(".edit-image-crop-y", widget).val()),
          parseInt($(".edit-image-crop-width", widget).val()),
          parseInt($(".edit-image-crop-height", widget).val())
        ]
      });
    });
  };
  
};



/* $Id: imagefield_crop.js,v 1.1.2.3.2.10 2009/11/11 08:12:53 yhager Exp $ */

Drupal.behaviors.imagefield_crop = function (context) { 
  // wait till 'fadeIn' effect ends (defined in filefield_widget.inc)
  setTimeout(attachJcrop, 1000, context);

  function attachJcrop(context) {
    if ($('.cropbox', context).length == 0) {
      // no cropbox, probably an image upload (http://drupal.org/node/366296)
      return;
    }
    $('.cropbox', context).each(function() {
      var self = $(this);
      
      // get the id attribute for multiple image support
      var self_id = self.attr('id');
      var id = self_id.substring(0, self_id.indexOf('-cropbox'));

      // get the name attribute for imagefield name
      var widget = self.parent().parent();

      $(this).Jcrop({
        onChange: function(c) {
          var preview = widget.parent().find('.widget-preview');
          // skip newly added blank fields
          if (undefined == Drupal.settings.imagefield_crop[id].preview) {
            return;
          }
          var rx = Drupal.settings.imagefield_crop[id].preview.width / c.w;
          var ry = Drupal.settings.imagefield_crop[id].preview.height / c.h;
          $('.jcrop-preview', preview).css({
            width: Math.round(rx * Drupal.settings.imagefield_crop[id].preview.orig_width) + 'px',
            height: Math.round(ry * Drupal.settings.imagefield_crop[id].preview.orig_height) + 'px',
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
        aspectRatio: Drupal.settings.imagefield_crop[id].box.ratio,
        boxWidth: Drupal.settings.imagefield_crop[id].box.box_width,
        boxHeight: Drupal.settings.imagefield_crop[id].box.box_height,
        setSelect: [
          parseInt($(".edit-image-crop-x", widget).val()),
          parseInt($(".edit-image-crop-y", widget).val()),
          parseInt($(".edit-image-crop-width", widget).val()) + parseInt($(".edit-image-crop-x", widget).val()),
          parseInt($(".edit-image-crop-height", widget).val()) + parseInt($(".edit-image-crop-y", widget).val())
        ]
      });
    });
  };
  
};



<div class="front-page-gallery">
<div class="views-left-bar">
  <span id="onelinegallery-left" class="views-left-button" style="left:-5px;top:12px;"></span>
</div>
<div class="views-right-bar">
  <span id="onelinegallery-right" class="views-right-button" style="right:-4px;top:12px;"></span>
</div>
<ul id="onelinegallery-gallery">
<?
$index = 0; $shown = 0;
foreach ($rows as $row): ?>
<li class="<?= ($shown++) >=8 ? 'hidden' : 'shown' ?>"><a href="#onelinegallery-<?=$index++?>"><?=$row['thumbnail']?></a></li>
<? endforeach; ?>
</ul>
<div>
<?
$index = 0;
foreach ($rows as $row): ?>
<div style="display:none; max-width: 500px;"  id="onelinegallery-<?=$index++?>">
<?=$row['image']?>
<h2><?=$row['title']?></h2>
<div><?=$row['description']?></div>
</div>
<? endforeach; ?>
</div>
<div style="clear:both;"></div>
</div>
<script type="text/javascript">

// set current dean info
jQuery._dean_total = <?=$index?>;
jQuery._current_dean = 0;
jQuery._dean_step = 8;

var gallery_item_fadeout = function(elems, base, start, stop, callback) {
  if (start < stop) {
    var cur = (base + stop - 1) % jQuery._dean_total;
    $(elems[cur]).fadeOut(100, function () {
      gallery_item_fadeout(elems, base, start, stop-1, callback);
      $(this).removeClass('shown').addClass('hidden');
    });
  }
  else {
    if (callback) {
      callback();
    }
  }
}

var gallery_item_fadein = function(elems, base, start, stop, callback) {
  if (start < stop) {
    var cur = (base + start) % jQuery._dean_total;
    $(elems[cur]).fadeIn(100, function () {
      gallery_item_fadein(elems, base, start+1, stop, callback);
      $(this).removeClass('hidden').addClass('shown');
    });
  }
  else {
    if (callback) {
      callback();
    }
  }
}

var deans_left_click = function () {
  $('#onelinegallery-left').unbind('click');
  $('#onelinegallery-right').unbind('click');
  
  var elems = $('#onelinegallery-gallery li');

  var new_current = jQuery._current_dean - jQuery._dean_step;
  if (new_current < 0) new_current = 0;

  gallery_item_fadeout(elems, jQuery._current_dean, 0, jQuery._dean_step, function () {
    gallery_item_fadein(elems, new_current, 0, jQuery._dean_step, function () {
      $('#onelinegallery-left').click(deans_left_click);
      $('#onelinegallery-right').click(deans_right_click);
    });
  });
  // elems.hide();
  // for (var i=new_current; i < new_current + jQuery._dean_step && i < elems.size(); i++)
  //   $(elems[i]).show();
  
  jQuery._current_dean = new_current;
  

};

var deans_right_click = function () {
  $('#onelinegallery-left').unbind('click');
  $('#onelinegallery-right').unbind('click');
  
  var elems = $('#onelinegallery-gallery li');
  var new_current = jQuery._current_dean + jQuery._dean_step;
  if (jQuery._dean_total < jQuery._dean_step) {
    new_current = 0;
  }
  else if (new_current > jQuery._dean_total - jQuery._dean_step)
    new_current = jQuery._dean_total - jQuery._dean_step;

  gallery_item_fadeout(elems, jQuery._current_dean, 0, jQuery._dean_step, function () {
    gallery_item_fadein(elems, jQuery._current_dean, 0, jQuery._dean_step, function () {
      $('#onelinegallery-left').click(deans_left_click);
      $('#onelinegallery-right').click(deans_right_click);
    });
  });
  // elems.hide();
  // for (var i=new_current; i < new_current + jQuery._dean_step && i < elems.size(); i++)
  //   $(elems[i]).show();
  
  jQuery._current_dean = new_current;

};


$(function() {

$('#onelinegallery-gallery a').each(function() {
  $(this).fancyZoom({directory: '/misc/fancyzoom'});
});

// bind dean clicks
$('#onelinegallery-left').click(deans_left_click);
$('#onelinegallery-right').click(deans_right_click);

});
</script>
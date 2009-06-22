<style type="text/css">
.vertical-video-detail-items { display: none; }
.vertical-video-list img { padding: 0 !important; margin: 0 10px; }
.vertical-video-list-item { clear: both; padding: 5px; margin: 5px 0; border: 1px solid #ccc; border-radius: 5px; -webkit-border-radius: 5px; -moz-border-radius: 5px; height: 60px; }
.vertical-video-item-thumbnail { float: left; }
.vertical-video-item-body { font-size: 0.9em; }
</style>
<!--[if IE]>
<style type="text/css">
.vertical-video-list {display: none;}
</style>
<![endif]-->
<div class="vertical-video-list">
<? foreach ($rows as $row): ?>
  <div class="vertical-video-list-item" id="vertical-video-item-<?=$row['nid']?>">
    <div class="vertical-video-item-thumbnail"><a href="#vertical-video-<?=$row['nid']?>"><?=$row['thumbnail']?></a></div>
    <div class="vertical-video-item-title"><a href="#vertical-video-<?=$row['nid']?>"><?=$row['title']?></a></div>
    <div class="vertical-video-item-body"><?=$row['body']?></div>
  </div>
<? endforeach; ?>
</div>
<div class="vertical-video-detail-items">
  <? foreach ($rows as $row): ?>
    <div id="vertical-video-<?=$row['nid']?>" class="vertical-video-detail-item">
    <div id="vertical-video-swf-<?=$row['nid']?>"><?= swf($row['video'], array('flashvars' => array('width' => '200', 'height'=> '355')))?></div>
    <h3><?=$row['title']?></h3>
    <div class="vertical-video-item-body"><?=$row['body']?></div>
    </div>
  <? endforeach; ?>
</div>
<script type="text/javascript">
$(function() {
  $('.vertical-video-list a').each(function() {
    $(this).fancyZoom({directory: '/misc/fancyzoom', width: 200, height: 390});
  });
});
</script>
<? /* 
<script type="text/javascript">
$(function() {
<? foreach ($rows as $row): ?>
$('#vertical-video-item-<?=$row['nid']?> a').each(function() {
  var href = $(this).attr('href').substring(1);
  $(this).fancyZoom({directory: '/misc/fancyzoom', width: 200, height: 390});
  $(this).click(function() {
      swfobject.embedSWF(
        "http://cms.upei.ca/futurestudents/sites/all/modules/swftools/shared/flash_media_player/player.swf",
        "vertical-video-swf-<?=$row['nid']?>",
        "200",
        "355",
        "7",
        "",
        {
          "autostart": "false",
          "width": "200",
          "height": "355",
          "playlist": "none",
          "controlbar": "over",
          "accessible_visible": "1",
          "file": "<?=$row['video']?>"
        },
        {
          "swliveconnect": "default",
          "play": "true",
          "loop": "false",
          "menu": "false",
          "quality": "autohigh",
          "scale": "showall",
          "align": "l",
          "salign": "tl",
          "wmode": "opaque",
          "bgcolor": "#FFFFFF",
          "version": "7",
          "allowfullscreen": "false",
          "allowscriptaccess": "sameDomain",
          "base": "http://cms.upei.ca/futurestudents/files/futurestudents/",
          "src": "http://cms.upei.ca/futurestudents/sites/all/modules/swftools/shared/flash_media_player/player.swf",
          "width": "200",
          "height": "355"
        },
        { "id": "swf-<?=$row['nid']?>"}
      );
  });
  pageTracker._trackPageview(Drupal.settings.basePath + 'click/' + href);
});
<? endfor; ?>
});
</script>
*/ ?>
<? $r = rand(0, count($rows)-1); ?>
<!--[if IE]>
<div class="vertical-video-single">
  <? print swf($rows[$r]['video'], array('flashvars' => array('width' => '200', 'height' => '355'))); ?>
</div>
<![endif]-->

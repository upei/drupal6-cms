<?php
if (is_numeric(arg(5)) && is_numeric(arg(6))) {
    $width = arg(5);
      $height = arg(6);
}
else {
  $width = 420;
  $height = 295;
}
foreach ($rows as $row):
?>
<!-- “Video for Everybody” by Kroc Camen <camendesign.com> cc-by -->
<video poster="<?=$row['cover']?>" width="<?=$width?>" height="<?=$height?>" controls="controls" style="background: black;">
  <source src="<?=$row['ogg']?>" type="video/ogg" />
  <source src="<?=$row['video']?>" type="video/mp4" />
  <object width="<?=$width?>" height="<?=$height?>" type="application/x-shockwave-flash"
  data="http://cms.upei.ca/media/sites/all/modules/swftools/shared/flash_media_player/player.swf" flashvars="streamer=lighttpd&amp;width=<?=$width?>&amp;height=<?=$height?>&amp;shuffle=false&amp;autostart=false&amp;skin=/misc/modieus/modieus.swf&amp;repeat=list&amp;playlist=none&amp;controlbar=bottom&amp;accessible_visible=1&amp;file=<?=urlencode($row['video'])?>&amp;image=<?=urlencode($row['cover'])?>"
  > <param name="movie" value="http://cms.upei.ca/media/sites/all/modules/swftools/shared/flash_media_player/player.swf" />
  <param name="flashvars" value="streamer=lighttpd&amp;width=<?=$width?>&amp;height=<?=$height?>&amp;shuffle=false&amp;autostart=false&amp;skin=/misc/modieus/modieus.swf&amp;repeat=list&amp;playlist=none&amp;controlbar=bottom&amp;accessible_visible=1&amp;file=<?=urlencode($row['video'])?>&amp;image=<?=urlencode($row['cover'])?>" />
    <!--[if gt IE 6]>
    <object width="<?=$width?>" height="<?=$height?>" classid="clsid:02BF25D5-8C17-4B23-BC80-D3488ABDDC6B">
      <param name="src" value="<?=$row['video']?>" /><!
    [endif]--><!--[if gt IE 6]><!-->
    <object width="<?=$width?>" height="<?=$height?>" type="video/quicktime" data="<?=$row['video']?>"
    > <param name="src" value="<?=$row['video']?>" />
    <!--<![endif]--><p>
      <strong>No video playback capabilities detected.</strong>
      Why not try to download the file instead?<br />
      <a href="<?=$row['video']?>">MPEG4 / H.264 “.mp4” (Windows / Mac)</a> |
      <a href="<?=$row['ogg']?>">Ogg Theora &amp; Vorbis “.ogv” (Linux)</a>
    </p><!--[if gt IE 6]><!--></object><!--<![endif]-->
    <!--[if gt IE 6]></object><![endif]-->
  </object>
</video>
<?php endforeach; ?>
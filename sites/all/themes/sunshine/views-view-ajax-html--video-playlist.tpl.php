<?php

if (is_numeric(arg(5)) && is_numeric(arg(6))) {
    $width = arg(5);
      $height = arg(6);
}
$playlist = array();
foreach ($rows as $row) {
    $playlist[$row['video']] = array('title' => $row['title'], 'description' => $row['body'], 'author' => 'University of Prince Edward Island', 'filepath' => $row['video'], 'fileurl' => $row['video'], 'thumbnail' => $row['cover']);
}

?>
<?
$content = str_replace("'", "\\'", swf($playlist,
    array('flashvars' => array( 'playlist' => 'over', 'autostart' => 'false', 'width' => $width, 'height' => $height), 'methods' => array('embed' => SWFTOOLS_NOJAVASCRIPT))
  ));
$content = explode("\n", $content);
$content = "'" . join("' + \n'", $content) . "'";
$iphone = <<<EOF
<video width="$width" height="$height" src="{$rows[0]['video']}" poster="{$rows[0]['cover']}">
  <source src="{$rows[0]['video']}" type="video/ogg" />
  <source src="{$rows[0]['video']}" type="video/mp4" />
  <object width="$width" height="$height" type="video/quicktime" data="{$rows[0]['video']}">
    <param name="src" value="{$rows[0]['video']}" />
  </object>
</video>
EOF;
$iphone = explode("\n", $iphone);
$iphone = "'" . join("' + \n'", $iphone) . "'";
?>

<script type="text/javascript">
if((navigator.userAgent.match(/iPhone/i)) || (navigator.userAgent.match(/iPod/i))) {
  document.write(<?=$iphone?>);
}
else {
  document.write(<?=$content?>);
}
</script>

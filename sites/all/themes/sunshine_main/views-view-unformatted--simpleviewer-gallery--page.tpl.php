<?php
$r = array();
foreach ($rows as $row) {
  $r[] = array(
    'fileurl' => $row['field_photo_fid_1']->content,
    'filename' => $row['field_photo_fid_1']->content,
    'description' => $row['title']->content,
  );
}

print swf($r,
  array(
    'flashvars' => array(
      'width' => '900',
      'height' => '600',
      ),
    'methods' => array(
      'embed' => SWFTOOLS_NOJAVASCRIPT,
      )
    )
);

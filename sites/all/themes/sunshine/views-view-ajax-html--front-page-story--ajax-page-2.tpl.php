<?php
  $row = $rows[0];
  unset($rows[0]);
  ?>
  <div id="front-page-topic-detail-<?=$row['topic_row']?>" class="topic-detail">
    <div class="first-topic">
      <?=$row['image_large']?>
      <div class="one-line-title"><a href="<?=$row['title_link']?>"><?=$row['one_line_title']?></a></div>
      <div class="one-line-summary"><?=$row['one_line_summary']?></div>
      <div class="push"></div>
    </div>
    <ul class="title-list">
    <? foreach ($rows as $row):?>
      <li><a href="<?=$row['title_link']?>"><?=$row['one_line_title']?></a></li>
    <? endforeach; ?>
    </ul>
  </div>
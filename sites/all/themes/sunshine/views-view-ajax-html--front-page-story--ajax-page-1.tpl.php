<?php for ($index = 0; $index < count($rows); $index ++):
$row = $rows[$index];
$node = $nodes[$index];
$link = base_path() . '/' . drupal_get_path_alias('node/' . $node->nid);
?>
  <li class="topic-list">
    <span class="v-id">#front-page-topic-detail-<?=$row['topic_row']?></span>
    <a href="<?=$row['title_link']?>"><?=$row['image_small']?></a>
    <div class="one-word-title"><a href="<?=$row['title_link']?>"><?=$row['one_word_title']?></a></div>
    <div class="four-word-summary"><a href="<?=$row['title_link']?>"><?=$row['four_word_summary']?></a></div>
    <div style="clear:both;"></div>
  </li>
<?php endfor; ?>

<div class="scrollable-container">
  <div class="navi"></div>
  <a class="prevPage"></a>
  <div class="scrollable">
    <div class="front-page-gallery">
    <div class="items">
      <?
      foreach ($rows as $row): ?>
      <div><a href="#onelinegallery-<?=$row['nid']?>"><?=$row['thumbnail']?></a></div>
      <? endforeach; ?>
      </div>
    <div>
      <? foreach ($rows as $row): ?>
      <div style="display:none; max-width: 500px;"  id="onelinegallery-<?=$row['nid']?>">
        <?=$row['image']?>
        <h2><?=$row['title']?></h2>
        <div><?=$row['description']?></div>
      </div>
      <? endforeach; ?>
      </div>
    </div>
  </div>
  <a class="nextPage"></a>
</div>

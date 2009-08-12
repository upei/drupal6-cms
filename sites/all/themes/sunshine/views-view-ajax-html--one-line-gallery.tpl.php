<div class="scrollable-container">
  <div class="navi"></div>
  <a class="prevPage"></a>
  <a class="nextPage"></a>
  <div class="scrollable">
    <div class="front-page-gallery">
    <div class="items">
      <?
      foreach ($rows as $row): ?>
      <div class="item"><a href="#onelinegallery-<?=$row['nid']?>"><?=$row['thumbnail']?></a></div>
      <? endforeach; ?>
      </div>
    <div>
      <? foreach ($rows as $row): ?>
      <div style="display:none; min-width: 350px; max-width: 500px;"  id="onelinegallery-<?=$row['nid']?>">
        <?=$row['image']?>
        <h2><?=$row['title']?></h2>
        <div><?=$row['description']?></div>
        <? if ($row['link']): ?>
          <div><?=$row['link']?></div>
        <? endif; ?>
      </div>
      <? endforeach; ?>
      </div>
    </div>
    <script type="text/javascript">
      $(function() {
        $('.front-page-gallery .item>a[href]').each(function() {
          $(this).fancyZoom({directory: '/misc/fancyzoom'});
          $(this).click(function() {
            var href=$(this).attr('href').substring(1);
            pageTracker._trackPageview(Drupal.settings.basePath + 'click/' + href);
          });
        });
        //$('.front-page-gallery .items div[rel]').overlay();
<?php $size = array_pop(arg()); ?>
        $('div.scrollable').scrollable({
          size: <?= is_numeric($size) ? intval($size): '8' ?>,
          loop: true
        });
      });
    </script>
  </div>
</div>

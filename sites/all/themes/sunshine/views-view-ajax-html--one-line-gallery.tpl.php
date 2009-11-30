<?php if (count($rows) > 0): ?>
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
          $(this).fancyZoom({directory: 'http://www.upei.ca/misc/fancyzoom'});
          $(this).click(function() {
            var href=$(this).attr('href').substring(1);
            pageTracker._trackPageview(Drupal.settings.basePath + 'click/' + href);
          });
        });
        // calculate the width automatically
        var size =Math.floor(
          $('.scrollable-container .front-page-gallery').width() / $('.scrollable-container .item').width()
        );
        $('div.scrollable').scrollable({
          size: size,
          loop: true
        });
      });
    </script>
  </div>
</div>
<?php endif; ?>

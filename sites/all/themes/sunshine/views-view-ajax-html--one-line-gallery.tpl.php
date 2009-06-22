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
      <div style="display:none; max-width: 500px;"  id="onelinegallery-<?=$row['nid']?>">
        <?=$row['image']?>
        <h2><?=$row['title']?></h2>
        <div><?=$row['description']?></div>
      </div>
      <? endforeach; ?>
      </div>
    </div>
    <script type="text/javascript">
      $(function() {
        $('.front-page-gallery .items a[href]').each(function() {
          $(this).fancyZoom({directory: '/misc/fancyzoom'});
          var href=$(this).attr('href').substring(1);
          pageTracker._trackPageview(Drupal.settings.basePath + 'click/' + href);
        });
        //$('.front-page-gallery .items div[rel]').overlay();
        $('div.scrollable').scrollable({
          size: 8,
          loop: true
        });
      });
    </script>
  </div>
</div>

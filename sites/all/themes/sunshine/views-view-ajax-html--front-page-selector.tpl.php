<script type="text/javascript"><!--//--><![CDATA[<!--
$(function() {
  
  $('#front-page-selector li.front-image-selector').each(function (index) {
  var li = $(this);

  li.click(function () {
    var li = $(this);
    window.location.href = li.find(".v-href").attr('href');
  });

  li.mouseover(function() {
    var li = $(this);
    $('#front-page-selector')
      .find('.front-image')
        .css('background-image', 'url(' + li.find('img').attr('src') + ')')
        .click(function () {
          var win = $(this);
          window.location.href = li.find(".v-href").attr('href');
        })
      .end()
      .find('.front-image-text').text(li.find('.v-title').text())
      .end()
      .find('.front-image-description').text(li.find('.v-description').text());
  });
  if (li.find('.v-default').size() > 0) {
    li.mouseover();
  }
  // iPhone support
  li.bind('touchstart', function () {
    li.mouseover();
  });
});

});//--><!]]>
</script>
<? $first = $rows[0]; unset($rows[0]); ?>
<div id="front-page-selector">
  <ul class="front-image-selector-list">
    <li class="front-image-selector">
      <span class="v-default">true</span>
      <span class="v-image"><?=$first['image']?></span>
      <span class="v-title"><?=$first['link_title']?></span>
      <span class="v-description"><?=$first['body']?></span>
      <a class="v-href" href="<?=$first['url']?>"><?=$first['title']?></a>
    </li>
<? foreach ($rows as $row): ?>
    <li class="front-image-selector">
      <span class="v-title"><?=$row['link_title']?></span>
      <span class="v-description"><?=$row['body']?></span>
      <span class="v-image"><?=$row['image']?></span>
      <a class="v-href" href="<?=$row['url']?>"><?=$row['title']?></a>
    </li>
<? endforeach; ?>

  </ul>

  <div class="front-image" style="background-image:url(<?=$first['image-url']?>);">
    <div class="front-image-hover" style="background-image:url(http://cms.upei.ca/misc/pic/swoosh490.png);">
      <div class="front-image-content">
        <h2 class="front-image-text"><?=$first['link_title']?></h2>
        <div class="front-image-description"><?=$first['body']?></div>
      </div>
    </div>
  </div>
  <div style="display: none;" id="front-image-loader"></div>
</div>


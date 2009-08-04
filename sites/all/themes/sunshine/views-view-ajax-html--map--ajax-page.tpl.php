<ul class="search-result">
<?php foreach ($rows as $row): ?>
  <li><a href="#/facilities/building/ajax/html/<?=$row['nid']?>"><?=$row['title']?></a></li>
<?php endforeach; ?>
</ul>
<script type="text/javascript">
$('.search-result').find('a').click(function() {
  var href = $(this).attr('href').substring(1);
  $(this).parent().parent().parent().load(href);
});
</script>

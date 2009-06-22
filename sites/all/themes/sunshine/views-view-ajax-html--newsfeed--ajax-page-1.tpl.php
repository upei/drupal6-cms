<ul>
<? foreach ($rows as $row): ?>
  <li><a href="<?=$row['link']?>" rel="nofollow"><?=$row['title']?></a></li>
<? endforeach; ?>
</ul>

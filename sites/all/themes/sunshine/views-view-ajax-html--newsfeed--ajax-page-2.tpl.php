<ul>
<? foreach ($rows as $row): ?>
<li><a href="<?=$row['link']?>"><?=$row['title']?></a><br />
<?=$row['body']?></li>
<? endforeach; ?>
</ul>

<div class="item-list viewscarousel clear-block">
  <ul>
    <?php foreach ($rows as $row): ?>
      <li>
        <ul>
        <?php $row = unserialize($row);
        foreach ($row as $label => $value): ?>
        <li><?= $label ?>: <?= $value ?></li>
        <?php endforeach; ?>
        </ul>
      </li>
    <?php endforeach; ?>
  </ul>
</div>
<?php
exit;
?>

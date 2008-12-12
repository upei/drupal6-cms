  <ul>
    <?php foreach ($rows as $row): ?>
      <li>
        <ul>
        <?php foreach ($row as $label => $value): ?>
        <li><?= $label ?>: <?= $value ?></li>
        <?php endforeach; ?>
        </ul>
      </li>
    <?php endforeach; ?>
  </ul>

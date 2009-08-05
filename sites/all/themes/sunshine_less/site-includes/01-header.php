<!-- Primary Links sit above this. -->
<?php if ($logo): ?>
<div id="header-logo">
	<a href="<?=base_path()?>"><img src="<?php print $logo; ?>" alt="<?php print $head_title; ?>" /></a>
</div>
<?php endif; ?>

<?php if (variable_get('site_name','') && variable_get('site_slogan', '')): ?>
  <h1 class="header-title header-title-twin"><a href="<?=base_path()?>"><?=strtoupper(variable_get('site_name', ''))?></a></h1>
  <h1 class="header-title header-title-twin"><a href="<?=base_path()?>"><?=strtoupper(variable_get('site_slogan', ''))?></a></h1>
<? elseif (variable_get('site_name', '')): ?>
  <h1 class="header-title"><a href="<?=base_path()?>"><?=strtoupper(variable_get('site_name', ''))?></a></h1>
<? endif; ?>

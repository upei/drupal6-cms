<!-- Primary Links sit above this. -->
<!-- Setup in case its the AVC bucket -->
<?php
  $site = explode("/", request_uri());
  if($site[1] == "avc"){
    $avclogo =  "<img style=\"margin-left:5px;\" src=\"/banner/other/avctoplogo.jpg\">";
    $headerlogowidth = " style=\"width:255px;\"";
    $headertwinwidth = " style=\"width:362px;\"";
  }
?>

  <div id="header-logo"<?php echo $headerlogowidth;?>>
	<a href="/home"><img src="/banner/other/UPEI-Horizontal-Logo_200.jpg" width="213" height="40" alt="UPEI Logo" /></a>
  <?php echo $avclogo; ?>
</div>

<div id="header-search">
	<?php include dirname(__FILE__) . "/../mods/google.php"; ?>
</div>
<?php if (variable_get('site_name','') && variable_get('site_slogan', '')): ?>
  <h1 class="header-title header-title-twin"<?php echo $headertwinwidth;?>><a href="<?=base_path()?>"><?=strtoupper(variable_get('site_name', ''))?></a></h1>
  <h1 class="header-title header-title-twin"<?php echo $headertwinwidth;?>><a href="<?=base_path()?>"><?=strtoupper(variable_get('site_slogan', ''))?></a></h1>
<? elseif (variable_get('site_name', '')): ?>
  <h1 class="header-title"><a href="<?=base_path()?>"><?=strtoupper(variable_get('site_name', ''))?></a></h1>
<? endif; ?>

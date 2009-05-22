<!-- Primary Links sit above this. -->
<div id="bannersection" class="fullwidthdiv">
	<div id="bannerimg">
		<a href="/home"><img src="/banner/other/UPEI-Horizontal-Logo_200.jpg" width="213" height="40" alt="UPEI Logo" /></a>
	</div>
	
	<div class="googlesearcharea">
		<?php include dirname(__FILE__) . "/../mods/google.php"; ?>
	</div>
		<?php //if (_get_bucket()!='homey'): ?>
		<?php if (variable_get('site_name','') && variable_get('site_slogan', '')): ?>
		    <h1 class="site-title site-title-two"><a href="<?=base_path()?>"><?=strtoupper(variable_get('site_name', ''))?></a></h1>
		    <h1 class="site-title site-title-two"><a href="<?=base_path()?>"><?=strtoupper(variable_get('site_slogan', ''))?></a></h1>
		<? elseif (variable_get('site_name', '')): ?>
	    <h1 class="site-title"><a href="<?=base_path()?>"><?=strtoupper(variable_get('site_name', ''))?></a></h1>
		<? endif; ?>
		<? //endif; ?>
</div>

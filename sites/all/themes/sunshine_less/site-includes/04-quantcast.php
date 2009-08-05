<!-- google analytics/quancast code. -->
<script type="text/javascript">
var gaJsHost = (("https:" == document.location.protocol) ? "https://ssl." : "http://www.");
document.write(unescape("%3Cscript src='" + gaJsHost + "google-analytics.com/ga.js' type='text/javascript'%3E%3C/script%3E"));
</script>
<script type="text/javascript">
try {
var pageTracker = _gat._getTracker("<?=$_ga?>");
<? if ((_get_bucket() == 'home' && arg(0) == 'node' && arg(1) == '190')): // campuslinks page ?>
pageTracker._trackPageview("/404.html?page=" + document.location.pathname + document.location.search + "&from=" + document.referrer);
<? else: ?>
pageTracker._trackPageview();
<? endif; ?>

} catch(err) {}</script>
<!-- Start Quantcast tag -->
<script type="text/javascript">
_qoptions={
qacct:"p-73x8TBYuYZv9-"
};
</script>
<script type="text/javascript" src="http://edge.quantserve.com/quant.js"></script>
<noscript>
<img src="http://pixel.quantserve.com/pixel/p-73x8TBYuYZv9-.gif" style="display: none;" height="1" width="1" alt="Quantcast"/>
</noscript>
<!-- End Quantcast tag -->

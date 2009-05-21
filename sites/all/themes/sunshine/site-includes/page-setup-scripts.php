<script type="text/javascript" src="/misc/swfobject.js"></script>
<script type="text/javascript"><?php /* Needed to avoid Flash of Unstyle Content in IE */ ?> </script>
<!--[if lte IE 6]>
<script type="text/javascript"> 
    $(document).ready(function(){ 
        $(document).pngFix(); 
    }); 
</script> 
<![endif]-->
<?php if (array_key_exists(DRUPAL_AUTHENTICATED_RID, user_roles())): ?>
<link type="text/css" rel="stylesheet" href="<?= base_path() . drupal_get_path('theme', 'sunshine') ?>/css/admin.css" />
<?php endif; ?>
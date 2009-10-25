<!--[if lte IE 6]><style type="text/css">#sidebar-left { display: none; }</style><![endif]-->
<?php if ($sidebar_left): ?>
<div id="sidebar-left">
  <div id="sidebar-left-bar">
  <div id="sidebar-left-close" title="Toggle Left Sidebar"></div>
  </div>
  <div id="sidebar-left-content" class="hidden">
  <?php print $sidebar_left ?>
  </div>
  <script type="text/javascript">
    $('#sidebar-left-bar').click(function() {
      if ($('#sidebar-left-content').hasClass('hidden')) {
        $('#sidebar-left-content').removeClass('hidden');
        $('#sidebar-left').css('width', '200px');
        $('#sidebar-left').css('height', 'auto');
        $('#sidebar-left-close').addClass('enabled');
      }
      else {
        $('#sidebar-left-content').addClass('hidden');
        $('#sidebar-left').css('width', '20px');
        $('#sidebar-left').css('height', '120px');
        $('#sidebar-left-close').removeClass('enabled');
      }
    });
  </script>
</div>
<?php endif; // sidebar_left ?>

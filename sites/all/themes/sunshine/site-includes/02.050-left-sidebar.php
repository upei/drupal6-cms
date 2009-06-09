<!--[if lte IE 6]><style type="text/css">#sidebar-left { display: none; }</style><![endif]-->
<?php if ($sidebar_left): ?>
<div id="sidebar-left">
  <div id="sidebar-left-bar" class="ui-widget ui-helper-clearfix">
  <div id="sidebar-left-close" title="Toggle Left Sidebar" class="ui-state-default ui-corner-all"><span style="display: block;" class="ui-icon ui-icon-arrowthickstop-1-e"></span></div>
  </div>
  <div id="sidebar-left-content" class="hidden">
  <?php global $user; if (in_array('super admin', $user->roles) || in_array('content manager', $user->roles)): ?>
  <a href="<?=url($_GET['q'], array('query'=>'_nocache=1'))?>">Flush AJAX Cache</a><br />
  <?php endif; ?>
  <?php print $sidebar_left ?>
  </div>
  <script type="text/javascript">
    $('#sidebar-left-bar div').hover(
      function() { $(this).addClass('ui-state-hover'); },
      function() { $(this).removeClass('ui-state-hover'); }
    );
    $('#sidebar-left-bar').click(function() {
      if ($('#sidebar-left-content').hasClass('hidden')) {
        $('#sidebar-left-content').removeClass('hidden');
        $('#sidebar-left-close span').toggleClass('ui-icon-arrowthickstop-1-e');
        $('#sidebar-left-close span').toggleClass('ui-icon-arrowthickstop-1-w');
        $('#sidebar-left').css('width', '200px');
        $('#sidebar-left').css('height', 'auto');
      }
      else {
        $('#sidebar-left-content').addClass('hidden');
        $('#sidebar-left-close span').toggleClass('ui-icon-arrowthickstop-1-e');
        $('#sidebar-left-close span').toggleClass('ui-icon-arrowthickstop-1-w');
        $('#sidebar-left').css('width', '20px');
        $('#sidebar-left').css('height', '120px');
      }
    });
  </script>
</div>
<?php endif; // sidebar_left ?>

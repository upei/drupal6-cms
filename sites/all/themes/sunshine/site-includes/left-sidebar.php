<!--[if lte IE 6]>
<style type="text/css">
#sidebar-left {display: none;}
</style>
<![endif]-->
<?php if ($sidebar_left) { ?>
        <div id="sidebar-left" style="width:20px;height:120px;">
          <div id="sidebar-left-bar" class="ui-widget ui-helper-clearfix" style="display: block; float: right;">
          <div id="sidebar-left-close" title="Toggle Left Sidebar" style="display: inline-block; width: 18px; height: 18px;" class="ui-state-default ui-corner-all"><span style="display: block;" class="ui-icon ui-icon-arrowthickstop-1-e"></span></div>
          </div>
          <div id="sidebar-left-content" class="hidden">
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
      <?php } ?>

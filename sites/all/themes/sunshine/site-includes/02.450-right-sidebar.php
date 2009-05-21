      <?php if ($sidebar_right) { ?>
        <div id="sidebar-right">
          <div id="sidebar-right-bar" class="ui-widget ui-helper-clearfix" style="display: block; float: left;">
          <div id="sidebar-right-close" title="Toggle Right Sidebar" style="display: inline-block; width: 18px; height: 18px;" class="ui-state-default ui-corner-all"><span style="display: block;" class="ui-icon ui-icon-arrowthickstop-1-e"></span></div>
          </div>
          <div id="sidebar-right-content">
          <?php print $sidebar_right ?>
          </div>
          <script type="text/javascript">
            $('#sidebar-right-bar div').hover(
              function() { $(this).addClass('ui-state-hover'); },
              function() { $(this).removeClass('ui-state-hover'); }
            );
            $('#sidebar-right-bar').click(function() {
              if ($('#sidebar-right-content').hasClass('hidden')) {
                $('#sidebar-right-content').removeClass('hidden');
                $('#sidebar-right-close span').toggleClass('ui-icon-arrowthickstop-1-e');
                $('#sidebar-right-close span').toggleClass('ui-icon-arrowthickstop-1-w');
                $('#sidebar-right').css('width', '200px');
                $('#sidebar-right').css('height', 'auto');
              }
              else {
                $('#sidebar-right-content').addClass('hidden');
                $('#sidebar-right-close span').toggleClass('ui-icon-arrowthickstop-1-e');
                $('#sidebar-right-close span').toggleClass('ui-icon-arrowthickstop-1-w');
                $('#sidebar-right').css('width', '20px');
                $('#sidebar-right').css('height', '120px');
              }
            });
          </script>
        </div>

      <?php } ?>


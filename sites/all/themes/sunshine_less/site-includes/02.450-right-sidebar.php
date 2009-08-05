      <?php if ($sidebar_right) { ?>
        <div id="sidebar-right">
          <div id="sidebar-right-bar">
          <div id="sidebar-right-close" class="enabled" title="Toggle Right Sidebar"></div>
          </div>
          <div id="sidebar-right-content">
          <?php print $sidebar_right ?>
          </div>
          <script type="text/javascript">
            $('#sidebar-right-bar').click(function() {
              if ($('#sidebar-right-content').hasClass('hidden')) {
                $('#sidebar-right-content').removeClass('hidden');
                $('#sidebar-right').css('width', '200px');
                $('#sidebar-right').css('height', 'auto');
              }
              else {
                $('#sidebar-right-content').addClass('hidden');
                $('#sidebar-right').css('width', '20px');
                $('#sidebar-right').css('height', '120px');
              }
              $('#sidebar-right-close').toggleClass('enabled');
            });
          </script>
        </div>

      <?php } ?>


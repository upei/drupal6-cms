<h2><a href="http://ic.upei.ca/events"><?php print t('Campus Event Calendar') ?></a></h2>
<script type="text/javascript">
Drupal.behaviors.override_assist_event_calendar = function (context) {

$('.page-front .month-view .inner, .page-view-calendar-event .month-view .inner').each(function() {                     
  var $this = $(this);
  // create inner popup node
  var node = $('<div class="inner-popup"></div>');
  // append to node
  $this.find('.calendar.monthview').appendTo(node);
  // make sure each item is viewable
  node.find('.calendar.monthview').show();
  // append inner popup to a day
  $this.append(node);
  $this.hover(function() {
      $this.find('.inner-popup').show();
    },  
    function() {
      $this.find('.inner-popup').hide();
    }   
  );  
});

}
</script>
<?php
$r = drupal_http_request('http://ic.upei.ca/events/views/embed/calendar_event/calendar_period_2');
print $r->data;


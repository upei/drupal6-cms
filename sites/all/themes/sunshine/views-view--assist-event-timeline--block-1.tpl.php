<?php
$cd = time();
$dateArray = array(
  array('date' => date('Y-m-d', mktime(0, 0, 0, date('m', $cd), date('d', $cd), date('Y', $cd))), 'text' => 'Today'),
  array('date' => date('Y-m-d', mktime(0, 0, 0, date('m', $cd), date('d', $cd) + 1, date('Y', $cd))), 'text' => 'Tomorrow'),
  array('date' => date('Y-m-d', mktime(0, 0, 0, date('m', $cd), date('d', $cd) + 2, date('Y', $cd))), 'text' => date('M j', mktime(0, 0, 0, date('m', $cd), date('d', $cd) + 2, date('Y', $cd)))),
  array('date' => date('Y-m-d', mktime(0, 0, 0, date('m', $cd), date('d', $cd) + 3, date('Y', $cd))), 'text' => date('M j', mktime(0, 0, 0, date('m', $cd), date('d', $cd) + 3, date('Y', $cd)))),
  array('date' => date('Y-m-d', mktime(0, 0, 0, date('m', $cd), date('d', $cd) + 4, date('Y', $cd))), 'text' => date('M j', mktime(0, 0, 0, date('m', $cd), date('d', $cd) + 4, date('Y', $cd)))),
);
?>
<h2><a href="http://ic.upei.ca/events/">Campus Events</a></h2>
<div id="event-timeline" class="wi-container">
  <? foreach ($dateArray as $date):?>
  <ul class="anchors" date="<?=$date['date']?>">
    <li><?=$date['text']?></li>
  </ul>
  <div class="wi-event-tooltip">
    <span class="wi-widget wi-event-tooltip-border-top-left"></span>
    <span class="wi-widget wi-event-tooltip-border-top-right"></span>
    <span class="wi-widget wi-event-tooltip-border-bottom-left"></span>
    <span class="wi-widget wi-event-tooltip-border-bottom-right"></span>
    <span class="wi-widget wi-event-tooltip-border-top"></span>
    <span class="wi-widget wi-event-tooltip-border-right"></span>
    <span class="wi-widget wi-event-tooltip-border-bottom"></span>
    <span class="wi-widget wi-event-tooltip-border-left"></span>
    <ul class="tooltips">
    </ul>
  </div>
  <? endforeach; ?>
  <div class="clear clear-block"></div>
  <div class="notes">
    Move the cursor over the timeline to show event names. Click event bars to see details.
  </div>
</div>
</div>

<script type="text/javascript">
jQuery(function() {
  var $ = jQuery;
  $('#event-timeline .anchors').each(function() {
    var anchor = $(this);
    $.get('http://cms.upei.ca/service/calendar/' + anchor.attr('date'),
      function(data, textStatus) {
        var doc = $(data);
        doc.find('event').each(function() {
          var dat = anchor.attr('date');
          var eventid = $(this).find('eventid').text();
          var title = $(this).find('title').text();
          var timebegin = $(this).find('timebegin').text();
          var link = $(this).find('link').text();
          anchor.append('<li eventid="' + dat + '-' + eventid + '"><a class="wi-widget wi-event-bar-normal" href="' +
            link +
            '" title="' +
            timebegin + ' ' + title +
            '"></a></li>'
          );
          anchor.next().find('.tooltips').append('<li id="event-' + dat + '-' + eventid + '"><span class="wi-widget wi-event-normal"></span><span class="event-content"><strong>' + timebegin + '</strong> ' + title + '</span></li>');
          anchor.find('li').hover(
            function() {
              var eventid = $(this).attr('eventid');
              $('#event-' + eventid).addClass('active');
              $('#event-' + eventid + ' .wi-event-normal').addClass('wi-event-active');
              $(this).addClass('wi-hover');
              $(this).find('a').addClass('wi-event-bar-active');
            },
            function() {
              var eventid = $(this).attr('eventid');
              $('#event-' + eventid).removeClass('active');
              $('#event-' + eventid + ' .wi-event-normal').removeClass('wi-event-active');
              $(this).removeClass('wi-hover');
              $(this).find('a').removeClass('wi-event-bar-active');
            }
          );
          anchor.hover(
            function() {
              var el = $(this).next();
              var pos = $(this).position();
              el.fadeIn();
              // reset height
              var width = el.find('.tooltips').outerWidth();
              var height = el.find('.tooltips').outerHeight();
              el.find('.wi-event-tooltip-border-left, .wi-event-tooltip-border-right').height(height);
              el.height(height);
              el.css({
                top: pos.top - el.outerHeight() + 30,
                left: pos.left + el.width() > $(window).width() ? $(window).width() - el.width() - 50: pos.left
              });
              el.find('.tooltips').addClass('inactive');
            },
            function() {
              var el = $(this).next();
              el.fadeOut();
              el.next('.tooltips').removeClass('inactive');
            }
          );
        });
      },
      'xml'
    );
  });
});
</script>

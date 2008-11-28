OVERVIEW
--------
The Views module allows administrators to create dynamic lists of content
for display in pages or blocks. It is possible to insert those lists into
existing node bodies and blocks, but such inclusion requires that PHP
filtering be turned on. The Insert View module allows any user to insert
view listings using tag syntax, without the need for PHP execution
permissions. The Insert View tag syntax for embedding a view is relatively
simple.

[view:my_view]
is replaced by the content listing corresponding to the named view. In this
case it is my_view.

[view:my_view=my_display]
invokes the my_view view using the my_display view display ID. If the display
slot is left empty, the view\'s "default" display is used.

See "HOW TO FIND A DISPLAY ID" below for help with display IDs.

Note: the display slot was previously used (in the Drupal 5 version) to provide
numeric limiters to control the number of nodes to display in a view. This sort
of local override has been deprecated in favor of taking advantage of Views
version 2's custom display functionality. See "UPGRADING FROM A PREVIOUS
VERSION" below for more information.

[view:my_view=my_display=1,2,3]
uses the my_display view display, and passes a comma delimited list of arguments
(in this case 1, 2, and 3) to the view.

Here's an example you could use with the default view named "tracker" which
uses the page display and takes a user ID as an argument:

[view:tracker=page=1]

In short this tag says, "Insert the view named tracker, use the "page" display,
and supply the argument 1."

Sometimes you want to pass an argument without specifying a display ID. You can
do that by leaving the display ID slot empty, like so:

[view:my_view==1]

In previous versions you could use the [view_pager:my_view] tag. It has been
deprecated in the Drupal 6 branch in favor of using views displays. See
"UPGRADING FROM A PREVIOUS VERSION" below for more information.

HOW TO FIND A DISPLAY ID
------------------------
On the edit page for the view in question, you'll find a list of displays at the
left side of the control area. "Defaults" will be at the top of that list. Hover
your mouse pointer over the name of the display you want to use. A URL will
appear in the status bar of your browser.  This is usually at the bottom of the
window, in the chrome. Everything after #views-tab- is the display ID. For
example in http://localhost/admin/build/views/edit/tracker?destination=node%2F51#views-tab-page
the display ID would be "page".

INSTALLATION
------------
Extract and save the Insert View folder in your site's modules folder and enable
it at admin/build/modules. Obviously, it requires the Views module to do its
magic.

Once Insert View is installed, visit the the input formats page at
/admin/settings/filters and click the "configure" link for the input format(s)
for which you wish to enable the Insert View Filter.  Then simply check the
checkbox for the filter.

IMPORTANT PERFORMANCE NOTE: To dispaly views correctly, Insert View turns off
caching for the input formats for which it is enabled. That means every node
using this input format will not be cacheable. This can impact site performance.
In these cases, it is recommended to create a special input format for use when
inserting views.

UPGRADING FROM A PREVIOUS VERSION?
----------------------------------
IF YOU UPGRADED FROM THE DRUPAL 5 VERSION OF INSERT VIEW:

THE LIMITERS SLOT IS NOW USED FOR DISPLAYS
Previously in Insert View the display slot was used to provide a numeric value
representing the number of nodes to display when showing the view. This has been
deprecated due to changes in Views version 2. With the ability to create custom
displays, we can use Views' functionality to make a unique view display to use
with Insert View. ALL EXISTING VIEWS USING THE NUMBER LIMITERS SHOULD CONTINUE
TO WORK, BUT WILL BE BASED OFF THEIR VIEWS' DEFAULT DISPLAY.

VIEW_PAGER SYNTAX HAS BEEN DEPRECATED
Previously in the Drupal 5 version, Insert View tags such as the one below could
be used to control the use of pagers in views. As of the Drupal 6 version,
however, you should simply use the settings in your views display to set the
pager. If your inserted view will require pager settings different than the base
view settings, simply create a new display via the Views interface and override
those settings.

Example of the deprecated tag: [view_pager:<name of view>=<number>]

CHANGES WITHIN THE DRUPAL 5 BRANCH OF INSERT VIEW:

In previous versions of Insert View (including the 2008-Jan-11 development snapshot
and earlier) it was was not required to enable the Insert View filter for input formats
(by visiting the /admin/settings/filters pages) because Insert View was a pseudo filter
and used hook_nodeapi() rather than the filter system.

Insert View now runs as a classic Drupal filter module, and that means it now works
in blocks.  If you upgrade your site and find Insert View tags aren't working, please
visit /admin/settings/filters and enable the Insert View Filter for each input format
necessary.
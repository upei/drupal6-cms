Table of Contents Module 2.3
============================

This is a module to generate a jQuery enabled mediawiki-like collapsible table
of contents section based on header tags.

Project Page: http://drupal.org/project/tableofcontents

Written by Andrew Berry with many contributions: andrewberry@sentex.net,
  http://drupal.org/user/71291

Sponsors have included the University of Guelph Central Student Association
(http://www.csaonline.ca/) and Pinchin Environmental (http://www.pinchin.com/).

Notable features:
	- Preserves attributes on the header tags
	- Checks for existing ID on headers and uses that if found (if none, creates one).
	- Handles duplicate heading titles cleanly when generating ID's.
	- jQuery script to make the Table of Contents collapsible. Currently using
	  the slideToggle function. Simply change line 4 of tableofcontents.js to
	  use a different transition. For more information on jquery and
	  transitions, see http://visualjquery.com.
	- Configurable minimum and maximum heading levels.
	- Able to configure options across the site, or on a per-page basis.
	- Sensible default theming and CSS. Both can be easily overridden in your
	  theme to make each Table of Contents look as you want.

1. Installation
---------------
a. place the contents of the tableofcontents directory in your modules directory. 
b. enable Table of Contents and Heading Anchors at admin/modules
c. enable the filters itself at admin/input formats, and add each of the desired
   filters to your input types. Be sure to set headinganchors to be before the 
   tableofcontents filter.
d. If you are using Drupal 6, or the HTML Corrector Filter in Drupal 5, the
   HTML Corrector filter must be placed *after* the Table of Contents filter.
   This is due to a bug in the HTML Corrector filter, which is included in
   Drupal 6: http://drupal.org/node/222926. Once this bug is fixed, then it
   will be able to be placed before these filters, ensuring that code being
   processed is correct.

2. Use
------
Place the table of contents marker (<!--tableofcontents-->) at any point in a
page to generate a table of contents at that location. It may be used multiple
times for muliple table of contents. The options defined in the first marker
will be used for all subsequent markers on the same body. Several options are
supported with the following syntax:

<!--tableofcontents option:value;-->
a. title: Override the default "Table of Contents" title. This setting is piped
   through t() for translation.

b. list: Choose an ordered list (ol) or an unordered list (ul).

c. minlevel: The minimum heading level for table of contents entries. Defaults to <h1>

d. maxlevel: The maximum heading level for table of contents entries. Defaults to <h3>

e. attachments: Choose to show attachments (1) or hide them (0). Defaults to 0.

e. Example marker with default values:
   <!--tableofcontents list:ol; title:Table of Contents; minlevel: 2; maxlevel: 3; attachments: 0;-->

3. Removal / Deinstallation
---------------------------
No database tables are created. To remove the module, just disable and delete
the module. The <!--tableofcontents--> tags may be removed if desired however,
the tag is an HTML comment so it will be ignored by the renderer when the
module is deleted (or the filter disabled).

4. Notes
--------
As I extended this module for use on in a specific site, I haven't had the
chance to test extensively across many themes and/or browsers. So far, it seems
to work fine on Zen, Bluemarine, Garland, and Bluebreeze on IE7, FF3, and
Safari. Different themes render ol and ul differently so you will probably
need to tweak the CSS to get the ToC to display to your liking for a particular
theme.

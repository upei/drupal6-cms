Table of Contents Module v2
===========================

This is a module to generate a jquery enabled mediawiki-like collapsible table
of contents section based on header tags (levels 1 to 5 max). It is based on
the "Table of Contents" module (Project Page:
http://drupal.org/project/tableofcontents) written by Andrew Berry
(andrewberry@sentex.net).

It is a complete rewrite of the original filter module as follows:
	+optimizes the code so that nothing is done, including loading the jquery &
	css files,  if the <!--tableofcontents--> marker does not appear in the text
	+preserves attributes on the header tags
	+checks for existing ID on headers and uses that if found (if none, creates one)
	+added jquery script to make the toc collapsible. Currently using the slideToggle.
	Simply change line 4 of tableofcontents.js to use a different transition.
	For more information on jquery and transitions, see http://visualjquery.com.
	+extends the minimum header level to 1
	+header conversion is case insensitive
	+made the regex match for options on the <!--tableofcontents--> marker tolerant
	of spaces
	+added a more explanatory error message for invalid options & concatenated it
	into a single string to prevent duplicate messages from being displayed
	+added several divs to make ToC themable via CSS
	+provided basic CSS
	

1. Installation
---------------
a. place the contents of the tableofcontents directory in your modules directory. 
b. enable Table of Contents and Heading Anchors at admin/modules
c. enable the filters itself at admin/input formats, and add each of the desired
   filters to your input types. Be sure to set headinganchors to be before the 
   tableofcontents filter.


2. Use
------
Place the table of contents marker (<!--tableofcontents-->) at any point in a
page to generate a table of contents at that location. It may be used multiple
times for muliple table of contents. Several options are supported with the
following syntax:

<!--tableofcontents option:value;-->
a. title: Override the default "Table of Contents" title. This setting is piped
   through t() for translation.

b. list: Choose an ordered list (ol) or an unordered list (ul).

c. minlevel: The minimum heading level for table of contents entries. Defaults to <h1>

d. maxlevel: The maximum heading level for table of contents entries. Defaults to <h3>

e. Example marker with default values:
   <!--tableofcontents list:ol; title:Table of Contents; minlevel: 1; maxlevel: 3;-->



3. Removal / Deinstallation
---------------------------
No database tables are created. To remove the module, just disable and delete the module.
The <!--tableofcontents--> tags may be removed if desired however, the tag is an HTML
comment so it will be ignored by the renderer when the module is deleted (or the filter disabled).



4. Notes
--------
As I extended this module for use on in a specific site, I haven't had the
chance to testextensively across many themes and/or browsers. So far, it seems
to work fine on Zen, Bluemarine, Garland, and Bluebreeze on IE7 and FF2.
Different themes render ol and ul differently so you will probably need to
tweak the CSS to get the ToC to display to your liking for a particular theme.



5. To Do
--------
a. make module themable
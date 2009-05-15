/* $Id: README.txt,v 1.4 2008/03/20 09:44:43 smk Exp $ */

-- SUMMARY --

The purpose of this module is to provide a central transliteration service for
other Drupal modules, as well as sanitizing the file names when uploading new
files.

For a full description visit the project page:
  http://drupal.org/project/transliteration
Bug reports, feature suggestions and latest developments:
  http://drupal.org/project/issues/transliteration


-- REQUIREMENTS --

None.


-- INSTALLATION --

1. Copy the transliteration module to your modules directory and enable it on
   the Modules page (admin/build/modules).

   During installation or update all filenames containing invalid characters
   will be automatically converted.

2. That's it. The names of all new uploaded files will now automatically be
   transliterated and cleaned from invalid characters.


-- INTEGRATION --

Module developers that want to make use of transliteration to clean input
strings should code similar to the following:

if (module_exists('transliteration')) {
  $transliterated = transliteration_get($string);
}

Take a look at transliteration.module for an explanation of additional function
parameters.


-- CONTACT --

Authors:
* Stefan M. Kudwien (smk-ka) - dev@unleashedmind.com
* Daniel F. Kudwien (sun) - dev@unleashedmind.com

This project has been sponsored by UNLEASHED MIND
Specialized in consulting and planning of Drupal powered sites, UNLEASHED
MIND offers installation, development, theming, customization, and hosting
to get you started. Visit http://www.unleashedmind.com for more information.

The transliteration is based on MediaWiki's UtfNormal.php
(http://www.mediawiki.org) and CPAN's Text::Unidecode library
(http://search.cpan.org/~sburke/Text-Unidecode-0.04/lib/Text/Unidecode.pm).


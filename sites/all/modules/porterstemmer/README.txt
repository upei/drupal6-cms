// $Id: README.txt,v 1.3 2009/07/14 23:38:47 jhodgdon Exp $

GENERAL INFORMATION
-------------------

This module implements the Porter-Stemmer algorithm, version 2, to
improve English-language searching with the Drupal built-in
Search module. Information about the algorithm can be found at
http://snowball.tartarus.org/algorithms/english/stemmer.html

Stemming reduces a word to its basic root or stem (e.g. 'blogging' to
'blog') so that variations on a word ('blogs', 'blogger', 'blogging',
'blog') are considered equivalent when searching. This generally
results in more relevant results.

Note that the Porter Stemmer algorithm is specific to American
English, so some British spellings will not be stemmed correctly.


INSTALLATION
------------
See the INSTALL.txt file for installation instructions.


TESTING
-------

The Porter Stemmer module includes tests for the stemming algorithm.
If you would like to run the tests, install the SimpleTest module from
http://drupal.org/project/simpletest, and then navigate to Administer
> Site building > Testing. 

Each "Stemming output" test for the Porter Stemmer module includes
approximately 2000 individual word stemming tests (which test the
module against a standard word list downloaded from the site above).
Due to the way output is displayed in SimpleTest, you may run into
browser timeout or memory issues if you try to run all 16 of the
"Stemming output" tests during the same test run.

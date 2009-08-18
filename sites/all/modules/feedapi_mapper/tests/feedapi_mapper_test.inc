<?php
// $Id: feedapi_mapper_test.inc,v 1.1.2.2 2009/07/13 19:59:52 alexb Exp $

/**
 * @file
 * Helper class with auxiliary functions for feedapi mapper module tests
 *
 * @todo: assert HTTP status after each post/get
 */

/**
 * Base class for implementing FeedAPI Mapper test cases.
 */
class FeedApiMapperTestCase extends DrupalWebTestCase {
  var $admin_user;

  // NOTE: This class doesn't implement setUp() - each subclass should!


  /**
   * Create a new Feed, and configure FeedAPI mapper to use this field to map to
   * either a custom content type, or a newly created one.  Refresh the items on
   * creation.
   * @param $options
   *   A keyed array of parameters used to create the Feed and perhaps the new
   *   content type.
   *   $options['typename']    (Optional) If set the mapper will create items of this type.
   *                            Otherwise see 'fields')
   *   $options['fields']      (Optional) An array of fieldname=>fieldtype elements that will
   *                            be used to create a custom content type. E.g:
   *                            array('beta' => 'number_integer'))
   *   $options['taxonomy']    The form values to configure a new Vocabulary which is attached
   *                           to the newly created typename above.
   *   $options['filename']    The basename of a file in feedapi_mapper/tests/samples
   *                           that will be used as the Feed URL
   *   $options['mappers']     (Optional) a list of mappers to be checked for on the mapping
   *                           screen.  E.g: array('node', 'content')
   *   $options['mapping']     The form values to configure the mapping
   *
   *   NOTE: a few values are written back into $options to notify the caller about
   *   the creation of the feed:
   *   $options['typename']    If this is not passed, the value that is created is stored here.
   *   $options['taxonomy'][vocab name][vocabulary]   Is filled with the Vocabulary object
   *                           from taxonomy_get_vocabularies
   *   $options['feed_url']
   *
   * @return the Url of the newly created Feed
   */
  function setupFeed(&$options) {
    // Create a content type
    if (!isset($options['typename'])) {
      $options['typename'] = $this->_createContentType(NULL, $options['fields']);
    }
    $typename = $options['typename'];

    // Create a new Vocabulary and attach it to the named content type
    if (isset($options['taxonomy'])) {
      foreach ($options['taxonomy'] as $name => &$edit) {
        if (empty($name)) {
          $name = 'taxonomy_'. mt_rand();
        }
        $edit['name'] = $name;
        $edit["nodes[$typename]"] = $typename;
        $this->drupalGet('admin/content/taxonomy/add/vocabulary');
        $this->drupalPost('admin/content/taxonomy/add/vocabulary', $edit, 'Save');
        $this->assertNoText('Access denied');
        $this->assertText("Created new vocabulary $name.");

        // Figure out which vid we just created by looking for the last vocab
        // for this type.
        $vocabularies = taxonomy_get_vocabularies($typename);
        $voc = array_pop($vocabularies);
        $edit['vocabulary'] = $voc; // save the result back in $options

        // Look through the FeedAPI Mappings for a taxonomy mapping for an entry
        // that looks like
        //   'mapping[options->tags]' => serialize(array('taxonomy', 'taxonomy', [VOCABNAME])),
        // and replace VOCABNAME with the vocabulary id we just created
        //   'mapping[options->tags]' => serialize(array('taxonomy', 'taxonomy', $vid)),
        foreach ($options['mapping'] as &$szvalue) {
          $value = unserialize($szvalue);
          if ($value[0] == 'taxonomy' && $value[2] == $name) {
            $value[2] = (int) $voc->vid;
            $szvalue = serialize($value);
          }
        }
      }
    }

    // Create the Feed
    $source_url = url(
      drupal_get_path('module', 'feedapi_mapper') . '/tests/samples/' . $options['filename'],
      array('absolute' => TRUE));
    $feed_url = $this->createFeed($source_url, $typename);
    $options['feed_url'] = $feed_url;

    // Check the Mapping page contains the right mappers
    if (isset($options['mappers'])) {
      $this->drupalGet($feed_url . '/map');
      foreach ($options['mappers'] as $mapper) {
        $this->assertText("($mapper module)");
      }
    }

    // Configure the mapping
    foreach ($options['mapping'] as $source => $target) {
      $mapping = array(
        'source' => $source,
        'target' => $target,
      );
      $this->drupalPost($feed_url . '/map', $mapping, 'Add');
    }

    // Refresh nodes
    $this->drupalGet($feed_url . '/refresh');
    $this->assertText('new item(s) were saved. 0 existing item(s) were updated');
    return $feed_url;
  }

  /**
   * Delete the given Feed, and all it's items.
   * @param $feed_url
   *   The Url of the Feed node that should be deleted.
   */
  function deleteFeed($feed_url) {
    // Delete all the feed items
    $this->drupalPost($feed_url . '/purge', array(), 'Yes');
    $this->assertText('feed items have been deleted.');

    // Delete the feed
    $this->drupalPost($feed_url . '/edit', array(), 'Delete');
    $this->assertText('This action cannot be undone.');
    $this->drupalPost(NULL, array(), 'Delete');
    $this->assertText('has been deleted.');
  }

  /**
   * Create a new content-type, and add a field to it. Mostly copied from
   * cck/tests/content.crud.test ContentUICrud::testAddFieldUI
   * @param $typename
   *   (Optional) the name of the content-type to create, defaults to a random name.
   * @param $fields
   *   (Optional) an keyed array of $field_name => $field_type used to add additional
   *   fields to the new content type.
   * @return the name of the new typename
   */
  function _createContentType($typename = NULL, $fields = array()) {
    if ($typename == NULL) {
      $typename = 'simpletest'. mt_rand();
    }

    // Create the content type.
    $edit = array(
      'type' => $typename,
      'name' => $this->randomName(10),
    );
    $this->drupalPost('admin/content/types/add', $edit, 'Save content type');
    $admin_type_url = 'admin/content/node-type/'. $typename;

    // A lookup table to select the widget for each field type.
    $field_widgets = array(
      'date' => 'date_text',
      'datestamp' => 'date_text',
      'datetime' => 'date_text',
      'number_decimal' => 'number',
      'email' => 'email_textfield',
      'emimage' => 'emimage_textfields',
      'emaudio' => 'emaudio_textfields', 
      'filefield' => 'filefield_widget',
      'image' => 'imagefield_widget',
      'link' => 'link',
      'number_float' => 'number',
      'number_integer' => 'number',
      'nodereference' => 'nodereference_select',
      'text' => 'text_textfield',
      'userreference' => 'userreference_select',
    );

    // Create the fields
    foreach ($fields as $field_name => $field_type) {
      $this->assertTrue(isset($field_widgets[$field_type]), "Field type $field_type supported");
      $label = $field_name . '_' . $field_type . '_label';
      $edit = array(
        '_add_new_field[label]' => $label,
        '_add_new_field[field_name]' => $field_name,
        '_add_new_field[type]' => $field_type,
        '_add_new_field[widget_type]' => $field_widgets[$field_type],
      );
      $this->drupalPost($admin_type_url . '/fields', $edit, 'Save');

      // (Default) Configure the field.
      $edit = array();
      $this->drupalPost(NULL, $edit, 'Save field settings');
      $this->assertText('Added field ' . $label);
    }

    return $typename;
  }

  /**
   * Create a new Feed node using the given Url and item type.
   * @param $url
   *   the Url of the RSS/Atom/etc that this feed
   * @param $typename
   *   node type of feed items
   * @return url
   *   the Url of the new Feed node
   */
  function createFeed($url, $typename) {
    $edit = array(
      'title' => $this->randomName(),
      'feedapi[feedapi_url]' => $url,
      'feedapi[processors][feedapi_node][content_type]' => $typename,
    );
    $this->drupalPost('node/add/feed', $edit, 'Save');
    $this->assertText("Feed $edit[title] has been created.");
    return $this->getUrl();
  }

  /**
   * Enable one or both of the built-in parsers for the Feed content type.
   * @param $simplepie
   *   if TRUE then enable the SimplePie parser
   * @param $commonsyndication
   *   if TRUE then enable the Common Syndication parser
   */
  function enableParsers($simplepie = TRUE, $commonsyndication = FALSE) {
    // @todo: add support for CSV
    $edit = array(
      'feedapi[parsers][parser_simplepie][enabled]' => $simplepie,
      'feedapi[parsers][parser_common_syndication][enabled]' => $commonsyndication,
    );
    $this->drupalPost('admin/content/node-type/feed', $edit, 'Save content type');
    $this->assertText('The content type Feed has been updated.');
  }

  /**
   * Debug helper: write some content to a file in Drupal's temporary directory.
   * @param $filename
   *   the filename to write, defaults to 'out.html'.
   * @param $data
   *   the content to write, defaults to the current page content.
   */
  function writeFile($filename = 'out.html', $data = NULL) {
    $data = ($data == NULL) ?  $this->drupalGetContent() : $data;
    $filename = file_directory_temp() . '/feedapi_mapper_test_' . $filename;
    $this->assertTrue(file_put_contents($filename, $data), t('Wrote content to %filename', array('%filename' => $filename)));
    drupal_set_message("Wrote content to $filename");
  }
}

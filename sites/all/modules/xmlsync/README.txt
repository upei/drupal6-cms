// $Id: README.txt,v 1.1 2009/07/13 14:01:16 gzfelix Exp $

CONTENTS OF THIS FILE
---------------------

  * Introduction
  * Installation
  * Usage
  * XML Feed format
  * Todo List


INTRODUCTION
------------

Current Maintainer: Yuxing Huang <yxh@webinit.org>

XMLSync is a module to synchronize record-based XML documents with Drupal. It
reads a format-specified record-based well-formed XML document into a Drupal
node XMLSyncrhonym, and parses records in the XML document into XMLSyncrhonym
entities. A XMLSynchronym is a Drupal node that has many synchronym records.


INSTALLATION
------------

System requirement:

* PHP 5.1
* MySQL 5.1-production
* Drupal 6.x

Extract the files to the module directory and enable it.


USAGE
-----

After installation, a new permission 'administer xmlsync' and a new node type
XMLSynchronym are added to Drupal. After configuring the permission, you can
create a new XMLSynchronym node in the create content menu. You may choose
the XML type from URL or Content. XMLSync fetches the XML document directly
from the URL if it is properly set. Or you can paste the content directly into
the XML Content textarea if the type is set to Content. Save the node, and
mark down the node id.

Open admin/build/views and add a new view. The view uses Node as the base
table. Add a filter to get the node (nid) we just added. Add a XMLSynchronym
Record Data field, and set the XQuery Path to /data/name to get the name
(assuming we are using the xml feed below) of a course. XMLSyncrhonym
record arguments, sorting, and filtering are also supported.


XML FEED FORMAT
---------------

Here is a real-world example format of a XML feed supported by XMLSync module.

///////////////////////////////////////////////////////////////////////////////
<?xml version="1.0" encoding="utf-8"?>
<feed title="UPEI Timetable" description="UPEI Timetable Feed">
  <indexes>
    <key>data/department</key>
    <key>data/year</key>
    <key>data/semester-order</key>
    <key>data/name</key>
    <key>data/title</key>
  </indexes>
  <node title="A ST101J" description="Introduction to Japanese I" id="tt-1"
    last_update="2009-07-10T10:33:42-04:00">
    <data>
      <id>1</id>
      <department>Asian Studies</department>
      <year>1</year>
      <semester>First Semester</semester>
      <semester-order>1</semester-order>
      <name>A ST101J</name>
      <title>Introduction to Japanese I</title>
      <location>M 030</location>
      <time>M W F 10:30-11:20</time>
      <time-parsed>
        <day>Monday</day>
        <day>Wednesday</day>
        <day>Friday</day>
        <time>
          <start>10:30</start>
        </time>
      </time-parsed>
      <status>Open</status>
      <all-instructors>Hirokazu Mitsumura</all-instructors>
      <instructors>
        <name>Hirokazu Mitsumura</name>
      </instructors>
      <description/>
      <prereq/>
      <all-prereqs/>
    </data>
  </node>
  <node title="A ST201" description="Introduction to West Asia" id="tt-2"
    last_update="2009-07-10T10:33:42-04:00">
    <data>
      <id>2</id>
      <department>Asian Studies</department>
      <year>2</year>
      <semester>First Semester</semester>
      <semester-order>1</semester-order>
      <name>A ST201</name>
      <title>Introduction to West Asia</title>
      <location>K 210</location>
      <time>T TH 2:30-3:45</time>
      <time-parsed>
        <day>Tuesday</day>
        <day>Thursday</day>
        <time>
          <start>2:30</start>
        </time>
      </time-parsed>
      <status>Open</status>
      <all-instructors>TBA</all-instructors>
      <instructors>
        <name>TBA</name>
      </instructors>
      <description/>
      <prereq/>
      <all-prereqs/>
    </data>
  </node>
</feed>
///////////////////////////////////////////////////////////////////////////////

TODO LIST
---------

* Ability to show a single XMLSynchronym record with template support
* Better indexing with indexes tags.
* PostgreSQL support

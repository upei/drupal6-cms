// $Id: README.txt,v 1.10 2008/04/08 06:28:14 andremolnar Exp $

Drupal webfm.module README.txt
==============================================================================

The Drupal webfm.module presents a paradigm shift in file management for Drupal.
This file manager is based on heirarchical directory structure unlike the
traditional flat filesystem used to date.  Webfm uses AJAX to allow users to
arrange files on the server in the same way they do with file managers on their
personal systems. This ability to heirarchically arrange files greatly
enhances the  managability of large collections of data.

WebFM does not exclude the use of the upload.module or other modules that depend
on the flat filesystem schema.  WebFM uses the file_move and file_copy functions
from file.inc.

Bug reports can be sent to the email address in the credits area below.


Installation
------------------------------------------------------------------------------

  - Unzip the archive and copy the 'webfm' directory to your modules directory
  (ie:/sites/all/modules). Alternatively copy the tarball to the module directory
  if you can unzip it on the server.

  - Enable the module on Drupal's admin/modules page.  An install file
  updates the database with the necessary table additions.


Configuration
------------------------------------------------------------------------------
Configure the module at admin/settings/webfm. Note: The configuration assumes
that the 'File system path:' is set in the usual way at admin/settings/file-system.
All WebFM directories are sub-directories of this 'File System' path. Set
'Download method:' radio to 'Public' since the module manages the download.

  - Create the 'WebFM root directory'. If this directory doesn't already exist,
  the system will create it in the 'File System' root. Multi directory root paths
  must already exist inside the 'File System' directory. Set the directory
  permissions to 775 if the server is linux/bsd.

  - The icon path allows the user to substitute their own gifs. File names are
  hardcoded in the javascript so the icons will have to have identical names.

  - The 'Maximum resolution for uploaded images' input functions in the same
  fashion as the root upload.module.

  - The 'Date Format' radio buttons set the day/month order in the browser
  listing date field.

  - The 'Display metadata title' checkbox sets the browser to display metadata
  titles rather than the actual filename if the metadata tile exists. Renaming
  files that use the metadata title must be done via the metadata editor.  Note
  that node attachments always display the metadata title if available.

  - 'Default File Permissions' set the file level permissions for files inserted
  into the database.  The exception is file uploads that create a version
  overwrite whereby the new file inherits the permissions from the previous file.

  - Roles that are granted the 'access webfm' permission will receive additional
  configuration fields for root path, extension white list, max upload file size
  and max total upload size. Roles with the 'access webfm' right but without a
  root directory cannot access the filesystem.

  - The 'WebFM attachments' section allows WebFM to attach files to nodes.
  'Attachment List Properties' sets the presentation of attached files.

  - The 'IE Drag-and-Drop Normalization' is a sub-optimal solution for
  compensating for relative positioning in theme css.  This feature is only
  available to #1 user.

  - The 'Webfm javascript debug' checkbox is only useful for users interested
  in looking under the covers or who want to develop the module.

  - The WebFM cron is a 'stored procedure' used for database cleanup of file
  records that are deleted outside of the WebFM interface (ie: OS shell, ftp).
  This feature is only available to #1 user.

Set WebFM rights in admin/user/access per role.

  - 'administer webfm' confers full rights to a role. Admins can see and operate
  on all files, including files not in the database. Only admins can create
  directories and access admin/settings/webfm.

  - 'access webfm' allows a role to download/view files via the WebFM browser.
  Only files referenced by the webfm_file table in the database are accessible.
  Only owners of a file (and admins) can move a file or modify it's metadata.

  - 'view webfm attachments' allows a role to see files attached to nodes via
  WebFM.

  - 'webfm upload' allows a role with the 'access webfm' right to upload files
  via the WebFM browser. The user who uploads a file is the the owner of that
  file.

Admins and File owners can set the following file level permissions:
  - Public download: Allows the file to be downloaded anonymously even if
    .htaccess exists.

  - Role View/Download: Allows users of the same role to view/download the file.

  - Role Attach: Allows users of the same role to attach the file to nodes.

  - Role Full Access: Allows users of the same role to delete/rename/move the
    file.  File permission edits are not allowed by role.

Enable attachments in admin/settings/content-types/*type* for each content type
that will accept attachments (default is disabled).

A .htaccess file (apache servers) can be placed in the WebFM root (or sub-path)
to secure file access. Webfm streams downloads and thus your browser doesn't
require direct http access to the directories

Updating the menu cache by navigating to admin/build/menu may be necessary if
upgrading from an earlier version of the module with different internal paths.

Translations of the module require revising the string array at the top of
webfm.js.


Features
------------------------------------------------------------------------------

  - Application-like look and feel via AJAX
  - Drag and drop moves of files and directories
  - Attachment of files to multiple nodes - location independence allows dir
    restructuring to have no affect on attachment functionality
  - Drag and drop attachment ordering
  - Single file upload with version options for file overwrite
  - File delete/rename/move/attach/metadata/permissions menu options for admins
    or file owners
  - File menu options for users with role access set by file permission
  - File store-in-db/remove-from-db admin menu options
  - Directory create/rename/delete admin menu options
  - Directory search for files that respects view privileges
  - Home directory per role with WebFM access
  - Secure file download if .htaccess file used
  - Metadata editor for admins or file owners(fixed fields at this time)
  - Debug window option for admin javascript development


Usage
------------------------------------------------------------------------------

There are many ways to setup a file system hierarchy. The rules of any given
system must be applied carefully if security of data is important.

The basic rules for users in a role with 'access webfm' rights:

    * The role root directory defines the domain and all subdirectories are
      accessible to the user.
    * The user cannot navigate above the role root directory.
    * Only files in the webfm_file table are accessible. Files uploaded by the
      user are owned by the user and are automatically in the database. Only
      module admins can view/operate on files not in the database.
    * The user has full control over files that he/she owns that stay within an
      accessible role root domain. File permissions can be locked down so that
      only the owner/admins can see or operate on a file. File permissions can
      be opened up so that anyone within the role can view or operate on the
      file.
    * Users with 'access webfm' rights cannot create/delete/move/rename
      directories. Only module administrators (users with 'administer webfm'
      permission or #1 user) can control the directory structure.

Roles with 'access webfm' rights can be subsets of other roles with 'access webfm'
rights or they can be exclusive. Users can be members of multiple roles and will
consequently have a separate left-hand tree for each unique root directory
(roles can even share the same root directory).

It is difficult to foresee how diverse users of the module will choose to set up
their systems but the following simple examples are typical arrangements. Both
examples presume that the drupal file-system directory is set to 'files', the
WebFM module is installed and the 'WebFM root directory' is set to 'webfm'.

Example 1
---------

The site requires 1 class of privileged users (A) to administer the file system
and 2 classes of WebFM users (B & C) with access to file resources. Both roles
will be able to upload files. Some WebFM users are members of both B & C while
others are members of only one. Uploaded files are by default only accessible by
the file owner and admins.

    * A site administrator will create 3 the roles A, B and C. Role A will have
      the 'administer webfm' permission set in .../admin/user/access. B & C will
      have the 'access webfm' and the 'webfm upload' permission set.
    * WebFM settings will now have a fieldset for roles B & C where the root
      directory for each role is set. The root of B is set to 'B' which
      automatically creates the 'files/webfm/B' directory. The root of C is set
      to 'C' which creates the directory 'files/webfm/C'. A user who is a member
      of only one of B or C will see a single left-hand directory tree that
      contains their domain. They will have no access to files within the other
      role domain. Users who are members of both B & C will have two left-hand
      directory trees and have the ability to move files they own or control
      between the two domains.

      Role A's root directory is the 'WebFM root directory' and thus A users see
      only a single left-hand tree of the entire module file-sys.
    * In WebFM settings, the 'Default File Permissions' are configured with all
      checkboxes unset. This combination of default file permissions means that
      files that are uploaded will initially only be viewable by the B or C user
      doing the upload (owner) and by A users. Individual file permissions are
      editable by the file owner or A user to permit other users to view/attach/
      modify the file. One consequence of granting the permission 'Role Full
      Access' is that a non-admin user with a single domain could lose contact
      with their own file if a dual domain non-admin user moves it to the other
      domain.

Example 2
---------

The site requires 1 class of privileged users (A) to administer the file system
and 2 classes of users (B & C) with access to file resources. C is determined to
be a subset of B such that B can access it's own files as well as those of C. C
will not be able to upload files to the browser but will only be able to view/
download  or attach files to nodes. B will be able to upload files.

    * A site administrator will create 3 the roles A, B and C. Role A will have
      the 'administer webfm' permission set in .../admin/user/access. B & C will
      have the 'access webfm' permission set. B will also have the 'webfm upload'
      permission set.
    * WebFM settings will now have a fieldset for roles B & C where the root
      directory for each role is set. First the root of B is set to 'B' which
      automatically creates the 'files/webfm/B' directory. Next the root of C is
      set to 'B/C' which creates the directory 'files/webfm/B/C'. Since C is a
      sub-dir of B, role B will have access to C but C will not be able to
      navigate above it's root to see B's files. The left-hand directory tree
      will appear different for B & C. B's tree will start at 'B' and have a 'C'
      sub-directory (and potentially other sub-directories as set up by A). C's
      tree is a subset of B's tree.

      Role A's root directory is the 'WebFM root directory'.
    * In WebFM settings, the 'Default File Permissions' are configured with
      'Role View Access' and 'Role Attach Access' set. This combination of file
      permissions means that files that a B user uploads/moves into the C realm
      will by default be viewable by C and be attachable to nodes that C creates.
      A B file owner can manually modify the file permissions of each individual
      file to hide it or prevent it from being attached to content by a C user.
      Likewise the file permissions can be opened so that a C user can edit file
      attributes or move the file into another sub-directory of C.

In the above examples the site administrator may simply create the roles/access
rules and then let an A user configure WebFM for B & C.


To Do
------------------------------------------------------------------------------

  - Flexible metadata scheme and standards based access for data mining
  - API for content/metadata search/sort.


Credits / Contact
------------------------------------------------------------------------------

(c) 2007 Web Community Resource Networks
401 Richmond St. W., Suite 384, Toronto, ON, Canada  M5V 3A8
http://web.net

Bug reports, feature requests, or other comments can be made on the project page
at http://drupal.org/project/webfm.

The author and maintainer of the module is Rob Milne.  Andre Molnar contibuted
db queries and php. Paul Shales assisted in the early development of attachment
and context menuing.

A lot of the php source is based on the Drupal upload module.

Sources for the javascript are to be found all over the web.  I borrowed ideas
from open source forums and modified to my needs.  The starting point was the
drupalization of the mxfb project on SourceForge.  Little residue remains of
that GPL code but it gave me much inspiration.  The event handler is based on
http://ajaxcookbook.org (Creative Commons Attribution 2.5 License).

I cannot remember where all the icon gifs originated but their provinence is
open source.

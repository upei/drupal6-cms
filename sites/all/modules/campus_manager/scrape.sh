#!/bin/bash
#
# cms_mirror_bucket
#
# This script performs the following actions:
# 
# 1. Uses httrack to assemble a static copy of a drupal "bucket"
#
# 2. Replaces any instances of the strings ${source_site} or cms-dev.upei.ca with www.upei.ca
#
# 3. Copies the static files to the front-end proxy server
#
# Revisions:
#
# 2007-08-23 - Close to final version - BV
# 2007-08-25 - Added code to manage symlinks to .html and .xml files
# 2008-01-18 - Excluded files/ from httrack scan and added rsync to copy files directly - BV/DC
# 2008-06-24 * Yuxing Huang <gzfelix@gmail.com>
#	     - Add photo site support
#	     - Fix feed item links
#	     - Fix pagination with properly defined httrack output filename structure and replace links in html files 
#

# Record a few important values in variables
# Changed source_site from cms-dev.upei.ca dec 15th
source_site=cms.upei.ca
cache_directory=/var/cache/httrack
static_directory=/var/www-static
log_filename=/var/log/cms_mirror.log
sites_home=/var/www-d6/current/sites
photo_site=photo.ic.upei.ca

symlinks() {
	suffix=$1
	names=`find . -maxdepth 1 -name "*$suffix" | sed "s/$suffix//g"`
	for n in $names; do
		ln -sT "$n$suffix" "$n"
	done
}

# Check to see if scrapes have been disabled
if [ -f ${cache_directory}/disable_scrape ] ; then
	echo "The process that updates the public copy of your web site is temporarily disabled."
	exit 1
fi 

# If the first parameter is -f, set the ignore_exist flag and then shift the arguments over
# (so the second parameter becomes the first)
if [ "$1" == "-f" ]; then
        ignore_exist=1
        shift
fi

# get the bucket name
bucket=`echo $1 | sed -re 's/^([^/]+)\/.*$/\1/'`

# Check to ensure that a bucket name was specified
if [ "$1" == "" ]; then

	# No bucket was specified
        echo "You must specify a bucket to mirror!"

elif [ -d ${cache_directory}/$bucket ] || [ $ignore_exist ] ; then


	# Check to see if a lockfile exists, indicating that a scrape is already in progress
	scrape_lockfile=${cache_directory}/lockfile.$bucket
	if [ -f ${scrape_lockfile} ] ; then
		echo "A previous request to copy $1 has not yet completed."
		ls -l ${scrape_lockfile}
		exit 1;
	fi

	# Create a lockfile to record the fact that a scrape has begun
	touch ${scrape_lockfile}

	# The directory exists or we don't care -- go ahead and scrape the bucket
        echo `date` $bucket mirror started >> ${log_filename}

	# If the directory exists, remove any symbolic links it might contain
	# (These are recreated later)
	if [ -d ${cache_directory}/$bucket ] ; then
		find ${cache_directory}/$bucket -type l -exec rm {} \;
	fi

	echo "Beginning copy of content in /$1.  This may take several minutes."

	# Need to include fix-ie.css file explicitly
	HTTRACK_OPTS="--sockets=10 --timeout=90 --retries=5 --host-control=1 -O ${cache_directory}/$bucket -N %h%p/%n%[page:-].%t -f -q -z -%p -b0"
	HTTRACK_OPTIONS="+${source_site}/$bucket/link/*
      -${source_site}/news/newsfeed/*
      -${source_site}/$bucket/files/*
      +${source_site}/$bucket/*/imagecache/*
      +${source_site}/$bucket/sites/all/*
			+${photo_site}/d/*
			${HTTRACK_OPTS}"

	# Scrape the bucket
	if [ x$2 == x ]; then
		httrack http://${source_site}/$1 \
	    http://${source_site}/$bucket/hidden/links -* \
		  +${source_site}/$1* \
			-r20 $HTTRACK_OPTIONS
	else
		# we need to go upstairs, but only direct links. old pages are not removed.
		httrack http://${source_site}/$1/$2 -* \
		  +${source_site}/$1/$2* \
			$HTTRACK_OPTIONS -r3 -X0 \
			+*.jpg +*.png +*.gif +*.js +*.css
	fi
	
  # check if index.html exists. if not, do a site scrape
	if [ ! -f ${cache_directory}/$bucket/${source_site}/$bucket/index.html ] ; then
	  httrack http://${source_site}/$bucket \
	    http://${source_site}/$bucket/hidden/links -* \
		  +${source_site}/$bucket* \
			-r20 $HTTRACK_OPTIONS
	fi

	echo `date` $1 mirror finished >> ${log_filename}

	echo "Preparing content to be copied."
	# This will copy the files directory from ${source_site} to upei.ca/$1/files

	# Check to see if files directories exists, create if necessary
	if [ ! -d ${cache_directory}/$bucket/${source_site}/$bucket/files ] ; then
		mkdir ${cache_directory}/$bucket/${source_site}/$bucket/files
	fi

	# Copy files from Drupal file store to cache directory
  rsync -av --delete --exclude "tmp/" \
    ${sites_home}/upei.ca.$bucket/files/ \
    ${cache_directory}/$bucket/${source_site}/$bucket/files/$bucket

	# Replace all instances of ${source_site} or cms-dev.upei.ca with www.upei.ca in captured HTML and XML files
	find ${cache_directory}/$bucket/${source_site}/$1/ -name "*html" \
		-exec sed -i 's/cms\(-dev\)\?\.upei\.ca/www.upei.ca/g' {} \;

	find ${cache_directory}/$bucket/${source_site}/$1/ -name "*xml" \
		-exec sed -i 's/cms\(-dev\)\?\.upei\.ca/www.upei.ca/g' {} \;

	# sync the photos from testbed.ip.upei.ca/d to www.upei.ca/photos
	if [ -d ${cache_directory}/$bucket/${photo_site} ]; then
		echo Copying from photo site ${photo_site} to www.upei.ca/photos
		mkdir -p ${cache_directory}/$bucket/${source_site}/$bucket/gallery2
		rsync -av --delete --exclude "tmp/" \
			${cache_directory}/$bucket/${photo_site}/d/* \
			${cache_directory}/$bucket/${source_site}/$bucket/gallery2
		rm -rf ${cache_directory}/$bucket/${photo_site}

		# HTML links fixes (href and src)
		# 1. convert photo_site links to www.upei.ca links
		find ${cache_directory}/$bucket/${source_site}/$bucket/ -name "*html" \
			-exec sed -r -i \
				-e "/(href|src)=/ {
					s%${photo_site}/d/%www.upei.ca/${bucket}/gallery2/%g
					}" {} \;
	fi
	# HTML links fixes
	# 1. pagination
	# 2. fix httrack's inappropriate treatment to feeds (deleted)
  # 3. fix jquery ui javascript
	find ${cache_directory}/$bucket/${source_site}/$1/ -name "*html" \
		-exec sed -r -i \
			-e "/(href|img.*src)=/ {
				s/href=\"([^?]+)\?page=([[:digit:]]+)[^\"]*\"/href=\"\1-\2\"/g
        s/src=\"([^?]+)\?[^\"]*\"/src=\"\1\"/g
			}" {} \;

# 2007-08-25 -- Don't think these next two sections are required now that symlinks are being created -- BV
#        # Add .html extensions to link URLs -rp
#        find ${cache_directory}/$1/${source_site}/$1/ -name "*xml" \
#                -exec sed -i 's/<\/link>/.html<\/link>/g' {} \;
#
#        # Add .html extensions to read more URLs -rp
#        find ${cache_directory}/$1/${source_site}/$1/ -name "*xml" \
#                -exec sed -i 's/\&quot\;\&gt\;read more/.html\&quot\;\&gt\;more/g' {} \;

	# Create extension-less symbolic links to .html and .xml files
	#dir_names=`find /var/cache/httrack/$bucket/${source_site}/$bucket -type d`

	# Doing it one directory at a time to ensure that symlinks are created relative to files
	# in the same directory.
	find /var/cache/httrack/$bucket/${source_site}/$bucket -type d | while read -d $'\n' dir_name
	do
		cd "$dir_name" 

		symlinks .html
		symlinks .xml

		check_name=../`basename "${dir_name}"`.html
		if [ -f "${check_name}" ] ; then
			ln -sT "${check_name}" index.html
		fi

	done

	echo "Copying content to public server."

	# Copy files to proxy server
	rsync -aWve "ssh -i /home/drupal/.ssh/id_rsa" ${cache_directory}/$bucket/${source_site}/${bucket}/ --delete drupal@prinny.cs.upei.ca:${static_directory}/$bucket/
  # copy banners and css to proxy server
  rsync -aWve "ssh -i /home/drupal/.ssh/id_rsa" /var/www-d6/docroot/css/ --delete drupal@prinny.cs.upei.ca:${static_directory}/css/
  rsync -aWve "ssh -i /home/drupal/.ssh/id_rsa" /var/www-d6/docroot/js/ --delete drupal@prinny.cs.upei.ca:${static_directory}/js/
  rsync -aWve "ssh -i /home/drupal/.ssh/id_rsa" /var/www-d6/docroot/banner/ --delete drupal@prinny.cs.upei.ca:${static_directory}/banner/
  rsync -aWve "ssh -i /home/drupal/.ssh/id_rsa" /var/www-d6/docroot/misc/ --delete drupal@prinny.cs.upei.ca:${static_directory}/misc/ 
 
  
	      echo `date` $1 rsync finished >> ${log_filename}
	
	echo "Copy has completed."

	# Remove our lockfile
	rm -f ${scrape_lockfile}
else

	# Destination directory doesn't exist and -f flag not specified -- display error and exit
        echo "The destination directory ${cache_directory}/$1 does not exist.  Aborting."

fi


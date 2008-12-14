#! /bin/bash
PASS=yupismal9!
#checks number of variables delivered from the command line
if [ $# != 1 ] ;
then
	echo "There should only be one variable!"
	exit 1;
fi

if [ -d /var/www/drupal/cms/current/sites/upei.ca.$1 ]; then
	# dump
	mysqldump -u cms_dev --password=$PASS $1 > /tmp/__upgrade_$1.sql
	# drop
	mysqladmin -h chinstrap.cs.upei.ca -P 3307 -u cms_dev --password=$PASS -f drop $1
	mysqladmin -h chinstrap.cs.upei.ca -P 3307 -u cms_dev --password=$PASS create $1
	echo "$1 created".
	mysql -h chinstrap.cs.upei.ca -P 3307 -u cms_dev --password=$PASS $1 < /tmp/__upgrade_$1.sql
	mysql -v -h chinstrap.cs.upei.ca -P 3307 -u cms_dev --password=$PASS $1 -e "UPDATE $1_system SET status=0 WHERE name='imagefield'"
	mysql -v -h chinstrap.cs.upei.ca -P 3307 -u cms_dev --password=$PASS $1 -e "CREATE TABLE $1_image ( \`nid\` INTEGER UNSIGNED NOT NULL, \`fid\` INTEGER UNSIGNED NOT NULL, \`image_size\` VARCHAR(32) NOT NULL, PRIMARY KEY (\`nid\`, \`image_size\`), INDEX image_fid(\`fid\`) )"
	mysql -v -h chinstrap.cs.upei.ca -P 3307 -u cms_dev --password=$PASS $1 -e "INSERT IGNORE INTO $1_image SELECT DISTINCT f.nid, f.fid, f.filename FROM $1_files f WHERE f.filename IN ('_original', 'thumbnail', 'preview', 'img_assist_properties', 'img_assist_custom') OR f.filename LIKE '%px wide'"
	#rm -f /tmp/__upgrade_$1.sql

	cp -ar /var/www/drupal/cms/current/sites/upei.ca.$1 /var/www-d6/current/sites/
	chown -R www-data.www-data /var/www-d6/current/sites/upei.ca.$1/files
	sudo -u www-data mkdir /var/www-d6/current/sites/upei.ca.$1/files/images/import
	sudo -u drupal mv /var/www-d6/current/sites/upei.ca.$1/themes/newsflash/css/override_style.css  /var/www-d6/docroot/css/$1.css
	sudo -u drupal mv /var/www-d6/current/sites/upei.ca.$1/themes/newsflash/images/graphic.jpg /var/www-d6/docroot/banner/$1.jpg
	rm -r /var/www-d6/current/sites/upei.ca.$1/themes
	rm -r /var/www-d6/current/sites/upei.ca.$1/modules

	echo "umm... i hope that worked"
else
	echo upei.ca.$1 does not exist.
fi

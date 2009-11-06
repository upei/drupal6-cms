#!/bin/bash

for file in *.png
do
  prefix=`basename $file .png`
  echo "[$prefix]"
  echo name = \"$prefix\"
  echo sequence = \"$file\"
# get the number in it
  num=`echo $prefix | sed -nre 's/[a-z0-9A-Z-]+-//p'`
  echo anchorX = $((num/2))
  echo anchorY = $((num/2))
  echo infoX = $((num/2))
  echo infoY = $((num/2))
done

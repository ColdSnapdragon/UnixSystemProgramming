#!/bin/bash

vmhgfs-fuse .host:/ /mnt/hgfs -o nonempty -o allow_other

file=$(pwd)/$1

cd /mnt/hgfs/share

if [ ! -f paste.txt ]; then
	touch paste.txt
fi

if [ ! -f $file ]; then
	echo -e "$file is not found, or it is not a regular file."
	exit 1
fi

cat $file > paste.txt

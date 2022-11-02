#!/bin/bash

vmhgfs-fuse .host:/ /mnt/hgfs -o nonempty -o allow_other

cd /mnt/hgfs/share

if [ ! -d roothome ]
	then
		mkdir roothome
fi

cd roothome

if [ ! -f log.txt ]
	then
		touch log.txt
fi

zip -r root$(date +%F-%H_%M) /root $> log.txt 

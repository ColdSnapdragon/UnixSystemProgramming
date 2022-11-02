#!/bin/bash

#把/tmp打包备份到share，并备注日期信息

vmhgfs-fuse .host:/ /mnt/hgfs -o nonempty -o allow_other

cd /mnt/hgfs/share

if [ ! -d tembk ] 
    then
	mkdir tembk
fi

if [ ! -f tembk/updata.txt ] 
    then
	touch tembk/updata.txt
fi

zip -r tembk/tembk$(date +%F-%H-%M-%S).zip /tmp -b tembk &> tembk/updata.txt
#zip没有专门指定目的位置的选项，实际上在压缩后的文件名前加上目录即可



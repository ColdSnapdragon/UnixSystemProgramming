#!/bin/bash

obj="root"

cd /root/Git/UnixSystemProgramming/

if [ -d "$obj" ]; then
	git rm -r $obj
	git commit -m "remove old /root $(date +%F)"
	rm -rf $obj
fi

cp -r /root ./
git add $obj
git commit -m "updata /root $(date +%F)"

git push

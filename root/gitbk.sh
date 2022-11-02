#!/bin/bash

obj="root"

cd /root/Git/UnixSystemProgramming/

git rm -r $obj
git commit -m "remove old /root $(date +%F)"
rm -rf $obj

cp -r /root ./
git add $obj
git commit "updata /root $(date +%F)"

git push

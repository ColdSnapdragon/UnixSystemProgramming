#!/bin/bash

read -p "Input the names of users: " -t 30 name
read -p "Input the number of users: " -t 30 num
read -p "Input the password of users: " -t 30 pass

if [ -z "$name" -o -z "$num" -o -z "$pass" ]
	then
		echo "非法输入！"
		exit 1
fi

con=$( echo $num | sed 's/[0-9]//g' )

if [ -z $con ]
	then
		touch /tmp/null
		for ((i=1;i<=num;++i))
			do
				useradd ${name}$i
				echo pass | passwd --stdin "${name}$i"
			done
fi

echo done
exit 0

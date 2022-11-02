#!/bin/bash
read -t 10 -n 5 -p "input string1(visual,maxlen:5) " str
echo -e "\noutput: $str\n"  #考虑到read可能截掉换行符，字符串结尾换行

read -t 30 -s -p "input string2(hiden): " str
echo -e "\noutput: $str"

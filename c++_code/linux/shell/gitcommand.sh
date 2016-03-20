#!/bin/bash
# this sh write by liushixiong
# main purpose to operate git command
# 										2016/03/18 13:25
# add if contament 
#										2016/03/19 21:54
#echo "$1"
#[ "$1" = "pull" ]
#echo $?
if [ "$1" = "pull" ]; then
	sudo git pull
	echo "hello"
else
	#git status > status.txt | grep "modified" | awk -F" " '{print $2}' 
	#not complete.
	sudo git add "$1"
	sudo git commit -m "$2"
	sudo git push
fi

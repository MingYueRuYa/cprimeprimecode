#!/bin/bash
# this sh write by liushixiong
# main purpose to operate git command
# 										2016/03/18 13:25
# add if contament 
#										2016/03/19 21:54
# update sh 
#										2016/03/20 15:24

if [ "$1" = "pull" ]; then
	sudo git pull
elif [ "$1" = "status" ]; then
	sudo git status
else
	git status | grep "modified" | awk -F" " '{print $2}' > tmp.txt
	while read commitfiles
	do
		sudo git add "$commitfiles"
	done < tmp.txt
	sudo git commit -m "$1"
	sudo git push
	echo "commit successfule."
	sudo rm -rf status.txt
	sudo rm -rf tmp.txt
fi

#!/bin/bash
# this sh write by liushixiong
# main purpose to operate git command
# 										2016/03/18 13:25
# add if contament 
#										2016/03/19 21:54
# update sh 
#										2016/03/20 15:24

ERROR_PARAMETER=100

Error_Msg()
{
	echo -e "$0:usage $0 -a \"filenames\" -m \"comments\" -status...\n"
	exit "$ERROR_PARAMETER"
}

#check paramter count
if [ $# -eq 0 ] ; then
	Error_Msg
fi

#p -> pull s -> status -A -> All -l -> log -m -> commit comment -a -> add
while getopts :pm:sal: OPTION
do
	case $OPTION in	
		p)
			sudo git pull
			;;
		s)
			sudo git status
			;;
		l) 
			number=$OPTARG
			sudo git log "-$number"
			;;
		m)
			msg=$OPTARG
			sudo git commit -m "$msg" > /dev/null 2>&1
			sudo git push > /dev/null 2>&1
			echo -e "\033[32mcommit successful\033[0m"
			;;
		a)
			shift `expr $OPTIND - 1`
			for file in $@
			do
				if [ `expr substr $1 1 1` == "-" ]
				then
					# add function to solve miss parameter problem.
					break
				fi
				sudo git add "$1"
				shift 1
			done
			;;
	esac
done


#if [ "$1" = "pull" ]; then
#	sudo git pull
#elif [ "$1" = "status" ]; then
#	sudo git status
#else
#	git status | grep "modified" | awk -F" " '{print $2}' > tmp.txt
#	while read commitfiles
#	do
#		sudo git add "$commitfiles"
#	done < tmp.txt
#	sudo git commit -m "$1"
#	sudo git push
#	echo -e "\033[32mcommit successful\033[0m"
#	sudo rm -rf status.txt
#	sudo rm -rf tmp.txt
#	exit 0
#fi

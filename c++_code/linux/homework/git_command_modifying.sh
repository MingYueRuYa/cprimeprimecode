#!/bin/bash
# this sh write by liushixiong
# main purpose to operate git command
# 										2016/03/18 13:25
# add if contament 
#										2016/03/19 21:54
# update sh 
#										2016/03/20 15:24
# update sh
#										2016/03/24 23:25
# update sh
#										2016/03/25 22:29


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

SolveParamter()
{
	_paramter="$1"
	case $_paramter in
		-p | p)
			sudo git pull
			;;
		-s | s)
			sudo git status
			;;
		-l | l) 
			_number="$2"
			sudo git log "-$_number"
			;;
		-m | m)
			_msg="$2"
			sudo git commit -m "$_msg" > /dev/null >&1
			if [ $? -ne 0 ] ; then
				break
			fi
			sudo git push > /dev/null >&1
			if [ $? -ne 0 ] ; then
				break
			fi
			echo -e "\033[32mcommit successful\033[0m"
			;;
		-A | A)
			_msg="$2"
			git status | grep "modified" | awk -F" " '{print $2}' > tmp.txt
			while read commitfiles
			do
				sudo git add "$commitfiles"
				if [ $? -ne 0 ] ; then
					break
				fi
			done < tmp.txt
			sudo git commit -m "$_msg" > /dev/null >&1
			if [ $? -ne 0 ] ; then
				break
			fi
			sudo git push > /dev/null >&1
			if [ $? -ne 0 ] ; then
				break
			fi
			echo -e "\033[32mcommit successful\033[0m"
			sudo rm -rf status.txt > /dev/null >&1
			sudo rm -rf tmp.txt > /dev/null >&1
			;;
		*)
			Error_Msg
			;;
	esac
}

#p -> pull s -> status -A -> All -l -> log
#-m -> commit comment -a -> add  -A auto commit modify files
startup()
{
	while getopts :pm:saA:l: OPTION
	do
		case $OPTION in	
			p)
				SolveParamter $OPTION
				;;
			s)
				SolveParamter $OPTION
				;;
			l) 
				SolveParamter $OPTION $OPTARG
				;;
			m)
				SolveParamter $OPTION $OPTARG
				;;
			a)
				shift `expr $OPTIND - 1`
				for file in $@
				do
					if [ `expr substr $1 1 1` == "-" ]
					then
						SolveParamter $1 $OPTARG
						continue
					fi
					sudo git add `find . -name "$1"` > /dev/null >&1
					if [ $? -ne 0 ] ; then
						break
					fi
					shift 1
				done
				;;
			A)
				SolveParamter $OPTION $OPTARG
			;;
		esac
	done
	exit 0
}

#start up funcion
startup $@

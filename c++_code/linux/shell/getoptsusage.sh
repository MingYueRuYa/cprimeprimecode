#!/bin/bash
#getopt usage

if [ $# -eq 0 ] ; then
	echo "Need paramter."
fi

# : 表示忽视错误，调用自己的异常判断
while getopts :anfv OPTION
do
	case $OPTION in
		a)
			echo "a parameter."
			echo "a $OPTIND"
			;;
		n)
			echo "n parameter."	
			echo "n $OPTIND"
			;;
		f)
			echo "f parameter."
			echo "f $OPTIND"
			;;
		v)
			echo "v parameter."
			echo "v $OPTIND"
			;;
		\?)
			echo "error msg."
			echo "v $OPTIND"
			;;
	esac
done

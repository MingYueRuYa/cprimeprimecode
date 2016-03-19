#!/bin/bash
#case 用法

echo -n "Input 1-3 number:"
read number;
case $number in 
	1)
		echo -e "you input 1.\n"
		;;
	2)
		echo -e "you input 2.\n"
		;;
	3)
		echo -e "you input 3.\n"
		;;
	*)
		echo -e "you input error number.\n"
esac

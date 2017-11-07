#!/bin/bash

PS3="favorite pet? "

select var in Dogs Cats Birds
do
	case $var in
		Dogs)
			echo "Dogs are my favorite pet"
			;;
		Cats)
			echo "Cats are my favorite pet"
			;;
		Birds)
			echo "Birds are my favorite pet"
			;;
		*)
			echo "none of my favorite pet"
			#exit 0 退出
			;;
	esac
	break
done

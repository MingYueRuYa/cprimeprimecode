#!/bin/bash

echo "Ctrl+d quit."
#while echo -n "Input your name:"; read name
#do
#	echo $name
#done

# read from file
#while read line
#do
#	echo $line
#done < testfile.txt

#break usage
#while :
#do
#	echo -n "Input number 1-5:"
#	read number
#	case $number in
#		1|2|3|4|5)
#			echo $number
#			;;
#		*)
#			echo "Your number is not 1-5 range."
#			break;
#			;;
#	esac
#done

#continue usage
while :
do
	echo -n "Input number 1-5:"
	read number
	case $number in
		1|2|3|4|5)
			echo $number
			;;
		*)
			echo "Your number is not 1-5 range."
			echo -n "Wrong number, continue(y/n)?"
			read iscontinue
			case $iscontinue in
				y|yes|Y)
					continue
					;;
				*)
					break
			esac
			;;
	esac
done

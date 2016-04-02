#!/bin/bash
DirName=test;
i=1;

while :
do
	i=`expr $i + 1`
	if [ $i -gt 50 ]; then
		exit 0
	else 
		mkdir "$DirName$i" 
		chmod 574 "$DirName$i"
	fi
done

#for i
#do
#	echo $i
#	if [ i -gt 50 ] ; then
#		exit 0
#	else 	
#		echo "hello"
#		i=`expr $i+1`
#		mkdir "$(DirName)i" 
#		echo "hello"
#	fi
#done

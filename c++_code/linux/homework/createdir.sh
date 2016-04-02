#!/bin/bash
DirName=test
#i=1;

#while :
#do
#	i=`expr $i + 1`
#	if [ $i -gt 50 ]; then
#		exit 0
#	else 
#		mkdir "$DirName$i" 
#		chmod 574 "$DirName$i"
#	fi
#done

for i in {0..49}
do
	#echo $i
	if [ -d "$DirName$i" ] ; then
		continue
	fi
	if [ $i -gt 50 ] ; then
		exit 0
	else 	
		mkdir "$DirName$i" 
		if [ $? -ne 0 ]; then
			echo "create dir error."
			exit 0
		fi
	fi
done
	echo "---------------------create successful-------------------"

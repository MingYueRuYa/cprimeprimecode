#!/bin/bash
GroupName=class1
index=0
groupadd $GroupName

while :
do
	i=`expr $i + 1`
	if [ $i -gt 21 ] ; then
		exit 0
	else 
		if [ $i -eq 1 ]; then
			useradd "std0$i" -G $GroupName
		else 
			useradd "std$i" -G $GroupName
		fi

	fi
done

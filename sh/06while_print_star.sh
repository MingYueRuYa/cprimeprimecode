#!/bin/bash
#使用while打印星号

if [ $# -lt 1 ]; then
	echo 'usage:$0 <n>'
	exit 1
fi

if [ $1 -lt 5 -o $1 -gt 15 ]; then
	echo 'usage:$0 <n>'
	echo ' where 5<=n<=15'
	exit 1
fi

#print star
currentrow=0
while [ ${currentrow} -lt $1 ]
do
	space=$[ $1-$currentrow-1 ]
	while [ $space -gt 0 ]
	do
		echo -n " "
		space=$[ $space - 1 ]
	done

	stars=$[ 2*$currentrow+1 ]	
	while [ $stars -gt 0 ]
	do
		echo -n "*"
		stars=$[ $stars - 1 ]
	done

	echo
	
	let currentrow+=1
done

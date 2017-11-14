#!/bin/bash

count=0

#条件不满足继续循环，当条件为真时退出循环
until [ $count -eq 3  ]
do
	echo "AAA"
	let count+=1
done

#!/bin/bash
#判断输入的文件名是否存在

echo -n "Input file name:"
read filename;

if [ -e $filename ]; then
	if [ -s $filename ]; then
		echo -e "$filename size is greate than 0.\n"
	else
		echo -e "$filename size is equal 0.\n"
	fi
else
	echo -e "$filename is not existed.\n"
fi


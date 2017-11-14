#!/bin/bash

# 查看录或某个文件是否存在

echo -n "enter a file name:"
read filename

#if [ "$filename" = "" ]; then
#    echo "filename can't empty."
#    exit 1
#fi

while [ "$filename" = "" ]
do
    echo "filename can't empty."
    echo -n "enter a file name:"
    read filename
done

if [ -e "$filename" ]; then
    echo "$filename is exists."
else
    echo "$filename not exists."
fi

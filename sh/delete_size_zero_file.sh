#!/bin/bash

# 删除文件大小为0文件-支持递归删除
# 参数小于2表示默认路径为当前路径，大于2指定其他路径
# 此脚本有个缺陷不能删除带空格的文件
if [ $# -eq 0 ]; then
    path=$(pwd)
else
    path=$1
fi

oldIFS="${IFS}"
IFS=$(echo -ne '\n\b')

for filename in `find $path -name "*"`
do
    if [ -d ${filename} ]; then
        continue
    fi
    a=$(ls -l "${filename}" | awk '{ print $5 }')
    if [ "$a" = "" ]; then
        continue
    fi
    if [ $a -eq 0 ]; then
         rm -v "${filename}"
    fi
done

ISF="${oldIFS}"
exit 0

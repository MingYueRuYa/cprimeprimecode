#!/bin/bash

# 删除文件大小为0文件-支持递归删除
# 参数小于2表示默认路径为当前路径，大于2指定其他路径
# 此脚本有个缺陷不能删除带空格的文件
if [ $# -eq 0 ]; then
    path=$(pwd)
else
    path=$1
fi

temppath=${path}

recursive_dir(){
    for filename in `ls $1`
    do
        deletefile="$1/${filename}"
        if [ -d ${deletefile} ]; then
            recursive_dir "${deletefile}"
        elif [ ! -e "${deletefile}" ]; then
            echo "${deletefile} is not exist."
        else
            size=$(ls -l "${deletefile}" | awk '{ print $5 }')
            if [ $size -eq 0 ]; then
                rm -v "${deletefile}"
            fi
        fi
    done
}

for filename in `ls ${temppath}`
do
    searchfile="${temppath}/${filename}"
    if [ -d ${searchfile} ]; then
        recursive_dir "${searchfile}"
    else
        a=$(ls -l "${searchfile}" | awk '{ print $5 }')
        if [ "$a" = "" ]; then
            continue
        fi
        if [ $a -eq 0 ]; then
            rm -v "${searchfile}"
        fi
    fi
done

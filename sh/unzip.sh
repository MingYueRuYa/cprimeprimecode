#!/bin/bash
zipname=$1 
if [ $# -eq 1 ]; then
   dirname=${zipname%.*}
else 
    dirname=$2
fi
echo ${zipname}
unzip -OGBK "${zipname}" -d ${dirname}

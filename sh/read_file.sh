#!/bin/bash

linesize=0
while read line
do
    echo ${line}
    let linesize+=1
done
echo "line count :${linesize}"

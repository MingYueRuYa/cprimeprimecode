#!/bin/bash

#shift 把位置参量向左移动

while  [ "$1" != "" ]
do
	echo "$@"
	shift
done

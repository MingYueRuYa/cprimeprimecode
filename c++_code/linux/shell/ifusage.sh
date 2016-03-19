#!/bin/bash
#if 用法

#这两种写法都是可以的，但是第一种写法更符合我的习惯
#if [ "13" -gt "12" ]; then
if [ "13" -gt "12" ]
then
	echo "great than."
else 
	echo "less than."
fi

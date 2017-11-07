#!/bin/bash

#默认使用"$@"，不会过滤掉""
echo '---------test "$@"-----------'
for i
do
	echo $i
done

echo '---------test "$@"-----------'

#过滤掉""，当成一个参数解析
echo '---------test $*-------------'
for i in $*
do
	echo $i
done
echo '---------test $*-------------'

#将所有的参数当做一个参数解析
echo '---------test "$*"-----------'
for i in "$*"
do
	echo $i
done
echo '---------test "$*"-----------'

#过滤掉""，当成一个参数解析
echo '---------test $@-------------'
for i in $@
do
	echo $i
done
echo '---------test $@-------------'

for i in `ls -a`
do
	if [ "$i" = "." -o "$i" = ".." ]; then
	#if [ "$i" != "." -a "$i" != ".." ]; then
		continue
	else
		echo $i
	fi
done

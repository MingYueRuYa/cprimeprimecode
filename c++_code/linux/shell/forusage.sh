#!/bin/bash
#usage for

#注意双引号加不加的区别
#for name in linux unix windows freeBSD
#do
#	echo $name
#done

#注意打印内容的时候是以空格+行为一行
#for content in `cat testfile.txt`
#do
#	echo $content
#done

i=1;
for param
do
	echo "param #$i is $param"
	i=`expr $i + 1`
done

#!/bin/bash
# this is shell operator gupiao data.

#1.找出2014-05-29的数据
grep "2014-05-29" gpdata.txt

#2.列出上海大盘2014-05月份的数据 
grep "2014-05-.." gpdata.txt

#3.列出2014-06月所有上涨的数据	
grep "2014-06" gpdata.txt | awk '{ if ($7 > 0) {print $1,"\t",$7}  }'
#4.统计上海大盘2014-05月所有上涨的数据 
grep "2014-05-.." | awk '{if ($7>0) print $1,"\t", $7}' | wc -l
#5.显示上海大盘2014-02月上涨幅度最大的一天	  
grep "2014-02" gpdata.txt | sort -n -k7 -r | head -1
grep "2014-02" gpdata.txt | sort -n -k7  | tail -1
grep "2014-02" gpdata.txt | sort -n -k7 -r | sed -n '1p'
#6.显示上海大盘2014-02月份所有上涨数据的时间和上涨的幅度(%)
grep "2014-02" gpdata_wbm.txt | awk '{ if ($7 > 0) {print $1,"\t", $7} }'
#7.显示上海大盘2014-02月份所有上涨数据的时间和上涨的幅度(%)，第5条-第10条之间的数据
grep "2014-02" gpdata_wbm.txt | awk '{ if ($7 > 0) {print $1,"\t", $7} }'
grep "2014-02" gpdata_wbm.txt | awk '{ if ($7 > 0) {print $1,"\t", $7} }' |sed -n "5,20p"
#8.列出上海大盘2014-02月份涨跌在1个点和2个点之间的数据
grep "2014-02" gpdata_wbm.txt | awk '{ if ($7 > 1 && $7 <2) {print $1,"\t", $7} }'
#9.在$HOME/myshell目录中查找*.sh的文件，检索*.sh文件中"case关键字出现的文件名和行号
find ./myshell/ -name "*.sh" | xargs grep "case" -n | awk '{print $1}'
find ./myshell/ -name "*.sh" | grep "case" -n | awk '{print $1}' 
find ./myshell/ -name "*.sh" | xargs grep "case" -n | awk '{print $1}' | awk -F: '{print $1,"\t "$2 }'
#command result
#./myshell/041/breakcon02.sh      8
#./myshell/041/breakcon02.sh      15
#./myshell/041/breakcon01.sh      8
#./myshell/041/case.sh    2
#./myshell/041/case.sh    5


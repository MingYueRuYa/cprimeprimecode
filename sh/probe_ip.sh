#!/bin/bash

# 探测IP地址
echo "" > ip.txt
a=10
while :
do
    let a+=1
    if [ $a -gt 255 ]; then
        break
    fi
    
    ip=$(ping -c 1 -W 3 192.168.10.${a} | grep "ttl" | awk '{ print $4}' \
         | sed 's/://g')
   
   if [ "${ip}" = "" ]; then
        echo "ping -c 1 192.168.10.${a} failed."
        continue
   fi

    echo "ping -c 1 192.168.10.${a} successful"
    echo ${ip} >> ip.txt

done

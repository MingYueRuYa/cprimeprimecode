#!/bin/bash

# 检查服务端口是否启动
n=1
echo "check server port..."

while :
do
    if [ $n -gt 20 ]; then
        break
    fi

    let n+=1
    port=`sudo netstat -antp | grep "0.0.0.0:22"`
    if [ ${#port} -gt 3 ]; then
        echo "server is starting..."
        break;
    fi
    sleep 3
done


#!/bin/bash

echo -n Count:
# 保存屏幕位置
tput sc

count=0;
while true;
do
    if [ $count -lt 40 ]; then
        let count++
        sleep 1
        # 回复屏幕位置
        tput rc
        # 删除当前光标位置后面
        tput ed
        echo -n $count
    else
        exit 0
    fi
done

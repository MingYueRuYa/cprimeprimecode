#!/bin/bash

# 测试命令执行的时间

start=$(date +%s)

sleep 2
cat ./*.sh > /dev/null

end=$(date +%s)

difference=$(( end-start ))
echo "time token to exeucte command is $difference seconds."

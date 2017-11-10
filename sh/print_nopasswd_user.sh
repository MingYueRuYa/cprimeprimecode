#!/bin/bash

echo "no password user are:"
# 注意换行符被替代成空格
echo $(sudo cat /etc/shadow | grep "!" | awk -F: '{ print $1 }')

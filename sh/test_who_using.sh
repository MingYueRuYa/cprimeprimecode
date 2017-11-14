#!/bin/bash

# 测试用户是否在线

echo -n "Please enter a user:"
read name
b=$(whoami)
if [ "$b" = "$name" ]; then
    echo "the user is running."
else
    echo "the user is not running."
fi

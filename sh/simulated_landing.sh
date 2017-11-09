#!/bin/bash

# 模拟shell登陆
echo -n "login:"
read name
echo -n "passwd:"
read passwd

if [ $name = "cht" -a $passwd = "abc" ]; then
    echo "the host adn password is correct."
else
    echo "the host adn password is error."
fi

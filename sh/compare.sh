#!/bin/bash

# 比较大小

echo "please enter two number:"
read a
read b

if [ $a -eq $b ];then
    echo "$a=$b"
elif [ $a -gt $b ]; then
    echo "$a>$b"
else
    echo "$a<$b"
fi

#!/bin/bash

# 不带参数表示pull，带参数的话表示需要提交

function help {
    echo "usage:"
    echo "$0 mean git pull "
    echo "$0 \"commit message \" mean git pull -> git commit -> git push"
    exit 0
}

case $1 in
    -h|-help|h)
        help
		;;
    -s|-statue|s)
        echo -e "\e[4m\e[1;32mgit status...\e[0m"
        git status 
        exit 0
		;;
    -m|-M) # 可以在改进此脚本
        :
        ;;
	*)
	    :
		;;
esac

echo -e "\e[4m\e[1;32mgit pull...\e[0m"
git pull

if [ $# -eq 0 ]; then
    exit 0 
fi

echo -e "\e[4m\e[1;32mgit commit -m $1\e[0m"
git commit -m "$1"

echo -e "\e[4m\e[1;32mgit push\e[0m"
git push

if [[ $? == 0 ]]; then
    echo -e "\e[4m\e[1;32mpush successful.\e[0m"
else
    echo -e "\e[4m\e[1;31mpush failed\e[0m"
fi


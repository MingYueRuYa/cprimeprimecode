#!/bin/bash

echo -e "\e[4m\e[1;32mgit pull...\e[0m"
git pull

if [ $# -eq 0 ]; then
    exit 0 
fi

echo -e "\e[4m\e[1;32mgit commit -m $1\e[0m"
git commit -m "$1"

echo -e "\e[4m\e[1;32mgit push\e[0m"
git push

#!/bin/sh

sudo apt-get update
sudo apt-get install g++
sudo apt-get install vim 
sudo apt-get install openssh-server
sudo apt-get install git
sudo apt-get install ctags

#git config
git config --global user.name "MingYueRuYa"
git config --global user.email "635672377@qq.com"

#generate key for www.github.com
ssh-keygen -t rsa -C "635672377@qq.com"

#clone address
#git clone git@github.com:/MingYueRuYa/cprimeprimecode.git


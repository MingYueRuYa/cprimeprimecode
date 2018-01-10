#!/bin/bash
set -x
mkdir $1
cp $1.rar ./$1
cd $1
unrar x $1.rar
rm $1.rar

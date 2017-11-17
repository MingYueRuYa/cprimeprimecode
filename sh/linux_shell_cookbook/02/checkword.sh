#!/bin/bash

word=$1

grep "^${word}$" /usr/share/dict/american-english -q

if [ $? -eq 0 ]; then
    echo $word is a dictionary word
else 
    echo $word is not a dictionary word
fi

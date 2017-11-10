#!/bin/bash

echo "git pull..."
git pull

if [ $# -eq 0 ]; then
    exit 0 
fi

echo "git commit -m $1"
git commit -m "$1"

echo "git commit -m $1"
git push

#!/bin/bash

count=1

for img in `find . -maxdepth 1 -iname '*.png' -o -iname '*.jpg' -type f `
do
    new=image-${count}.${img##*.}
    
    echo "rename ${img} to ${new}"

    mv ${img} ${new}
    let count+=1
done

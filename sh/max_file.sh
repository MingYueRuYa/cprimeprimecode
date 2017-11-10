#!/bin/bash

size=0

for filename in `ls -a`
do
    if [ ${filename} = "." -o ${filename} = ".." ]; then
        continue
    fi
    size_b=$(ls -la ${filename} | awk '{ print $5 }')
    if [ ${size_b} -gt ${size} ]; then
        size=${size_b}
        name=${filename}
    fi
done

echo "max file is:${name}"

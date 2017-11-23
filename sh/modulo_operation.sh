#!/bin/bash

for i in {1..100}
do
    # if (( i%3 == 0 )); then
    if [ $((i%3)) -eq 0 ]; then
        echo $i
    fi
done

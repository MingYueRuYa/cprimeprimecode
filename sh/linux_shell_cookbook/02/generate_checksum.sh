#!/bin/bash

PIDARRAY=()

for file in 1.iso 2.iso
do
    md5sum $file &
    PIDARRAY+=("$!")
done

echo ${PIDARRAY[@]}

wait ${PIDARRAY[@]}


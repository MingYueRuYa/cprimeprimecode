#!/bin/bash

count=0
while [ ${count} -lt 100  ];
do
    echo ${count} >> num.txt
    let count+=1
done


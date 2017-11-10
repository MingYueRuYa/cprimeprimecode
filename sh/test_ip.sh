#!/bin/bash

for i in 1 2 3 4 5 6 7 8 9
do
    echo "the number of $i computer is "
    ping -c 1 192.168.0.$i
done

ifconfig | grep "inet addr:" | awk '{ print $2 }' | sed 's/addr://g'

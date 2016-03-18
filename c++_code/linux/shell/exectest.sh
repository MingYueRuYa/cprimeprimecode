#!/bin/bash
exec 3<&0 0<name.txt
read line1
read line2

exec 0<&3

echo $line1
echo $line2

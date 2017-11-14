#!/bin/bash

count=0;
for i in *
do
	count=$[$[count]+1]
done

echo  "${count} files in current dir."

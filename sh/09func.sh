#!/bin/bash

function print {
	echo "parameter's count:$#"
	for i in "$@"
	do
		echo -n "$i "
	done
	echo -ne '\n'
}

print "1 2 3 "  6 5 liushixiong


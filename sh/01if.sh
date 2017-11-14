#!/bin/bash

if [ $# -ne 1 ]; then
	echo "usage:$0 name"
	exit 1
else
	echo "$1 successful."
fi

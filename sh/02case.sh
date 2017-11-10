#!/bin/bash

case $1 in
	A)
		echo "this is A."
		;;
	B | b)
		echo "this is B or b."
		;;
    y|Y|Yes|YES)
		echo "yes..."
		;;
    n|no|No|NO)
		echo "NO..."
		;;
	*)
		echo "this is others."
		;;
esac

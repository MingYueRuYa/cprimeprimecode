#!/bin/bash

case $1 in
	A)
		echo "this is A."
		;;
	B | b)
		echo "this is B or b."
		;;
	*)
		echo "this is others."
		;;
esac

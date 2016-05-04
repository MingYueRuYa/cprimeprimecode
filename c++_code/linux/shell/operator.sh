#!/bin/bash
# test symbol 
echo hello; echo there
filename=ttt.sh
if [ -r "$filename" ]; then
	echo "File $filename exists."; cp $filename $filename.bak
else
	echo "File $filename not found."; touch $filename
fi; echo "File test complete."

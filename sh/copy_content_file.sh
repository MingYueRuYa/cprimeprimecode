#!/bin/bash

savefile="sh.file"

echo "" > ${savefile}

filelist=$(find . -name "*.sh")

for filename in ${filelist}
do
    echo "----------------${filename}--------------------"  >> ${savefile}
    cat ${filename}  >> ${savefile}
    echo "----------------${filename}--------------------"  >> ${savefile}
    echo  >> ${savefile}
done

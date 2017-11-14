#!/bin/bash

#字符串操作

var=/aa/bb/cc
result1=${var#*/}
result2=${var##*/}
result3=${var%/*}
result4=${var%%/*}

echo ${var} 
echo '${var#*/}'="$result1"
echo '${var##*/}'="$result2"
echo '${var%/*}'="$result3"
echo '${var%%/*}'="$result4"

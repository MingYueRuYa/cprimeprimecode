#!/bin/bash

# -s 不回显，-n表示读取的字符
loopcount=0
aKey=(0 0 0 0 0 0)

cESC=`echo -ne "\033"`
cSpace=`echo -ne "\040"`

while :
do
    read -s -n 1 key

    aKey[0]=${aKey[1]}
    aKey[1]=${aKey[2]}
    aKey[2]=${aKey[3]}
    aKey[3]=${aKey[4]}
    aKey[4]=${aKey[5]}
    aKey[5]=$key

    if [[ ${aKey[0]} == $cESC && ${aKey[1]} == "[" \
          && ${aKey[2]} == "1" && ${aKey[3]} == ";" \
          && ${aKey[4]} == "5" && ${key} == "D" ]]; then
        echo KEYDOWN
    fi

done

exit 0

GetKey()
{
    aKey=(0 0 0)

    cESC=`echo -ne "\033"`
    cSpace=`echo -ne "\040"`

    while :
    do
        read -s -n 1 key
        #echo $key
        #echo "XXX"

        # ^[[A ^[表示ESC键，键盘按下方向键一共是3个键 ^[ [ A
        # 螺旋状的赋值有意思
        aKey[0]=${aKey[1]}
        aKey[1]=${aKey[2]}
        aKey[2]=$key

        if [[ $key == $cESC && ${aKey[1]} == $cESC ]]; then
          exit 0
        elif [[ ${aKey[0]} == $cESC && ${aKey[1]} == "[" ]]; then
           if [[ $key == "A" ]]; then 
             echo KEYUP
           elif [[ $key == "B" ]]; then 
             echo KEYDOWN
           elif [[ $key == "C" ]]; then 
             echo KEYRIGHT
           elif [[ $key == "D" ]]; then 
             echo KEYLEFT
           fi
        fi 
    done
}

GetKey

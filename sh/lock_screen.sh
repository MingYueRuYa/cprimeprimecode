#!/bin/bash

#捕捉 2(ctrl+c) 3(ctrl+\) 15(TERM)
trap "nice_try" 2 3 15

TTY=`tty`

nice_try()
{
	echo -e "\nNice try, the terminal stays locked"
}

#输入字符不回显，让密码不可见
stty -echo

echo -n "Enter your password to lock $TTY:"
read PASSWORD
clear
echo -n "Enter your password to unlock $TTY:"
while :
do
	read RESPONSE
	if [ "$RESPONSE" = "$PASSWORD" ]; then
		echo "unlocking..."
		break
	fi
	clear
	echo "wrong password and terminal is locked..."
	echo -n "Enter you password to unlock $TTY:"
done

#输入字符回显
stty echo

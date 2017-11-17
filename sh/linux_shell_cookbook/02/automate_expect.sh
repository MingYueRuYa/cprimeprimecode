#!/usr/bin/expect

spawn ./interactive.sh

expect "Enter number:"
send "2\n"
expect "Enter name:"
send "linux\n"
expect eof


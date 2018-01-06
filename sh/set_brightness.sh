#!/bin/bash
echo 456 > /sys/class/backlight/intel_backlight/brightness
# 如果要设置成开机启动的
# 将脚本放到/etc/rc.local
# /home/liushixiong/code/cprimeprimecode/sh/set_brightness.sh


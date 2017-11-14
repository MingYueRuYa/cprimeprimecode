#!/bin/bash

#trap 扑捉信号

trap "rm -f tmp$$;exit 0" 2 3
touch tmp$$
sleep 60

#!/bin/bash

sudo git add $1
echo $1
sudo git commit -m "$2"
sudo git push

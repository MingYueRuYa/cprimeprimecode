#!/bin/bash

echo 'alias rm="saferm(){ cp $@ ~/backup;rm $@; }; saferm $@"' \
    >> ~/.bashrc


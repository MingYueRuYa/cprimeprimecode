#!/bin/bash
zipname=$1
unzip -OGBK ${zipname} -d ${zipname%.*}

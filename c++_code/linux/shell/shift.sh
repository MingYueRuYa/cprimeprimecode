#!/bin/bash
echo "first $0"
echo "second $1"
echo "third $2"
echo "fourth $3"
echo "start shift 2"
shift 2
echo "second $1"
echo "third $2"

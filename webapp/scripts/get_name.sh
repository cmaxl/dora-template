#!/bin/bash
# $1 directory that will be removed from the path
# $2 file name to process

# construct the variable name from the path and file name
# remove the leading ./, $1 and .gz extension
# replace / or . with _
name=$(echo $2 | sed -e "s/^\.\///" -e "s/$(echo $1 | sed 's/\//\\\//g')\///" -e "s/\.gz$//" | tr '/\.' '_')

echo $name
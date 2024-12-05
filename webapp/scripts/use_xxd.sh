#!/bin/bash
# $1 file to convert to a C array
# $2 name of the array to create
# $3 the output header file to append to

echo "const size_t ${2}_len = $(stat -f %z $1);" >> ./$3
echo "const uint8_t ${2}_GZ[] PROGMEM = {" >> ./$3
# use xxd and remove the first and last line of the output
xxd -i $1 | sed -e '2,$!d' -e 's/^/  /' -e '$d' | sed -e '$d' >>./$3
echo "};" >>./$3
echo "" >>./$3
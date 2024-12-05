#!/bin/bash
# $1 directory to search for .gz files
# $2 output header file to create

# create the header file and add the initial content
cat <<EOT >|./$2
#pragma once

/* vue-app header file 
*  Autogenerated during build by make_header.cjs
*  Do not edit this file directly
*  Changes to the source files should be made in the nodejs project
*/

EOT

# put all .gz files from the build directory and subdirectory into header using xxd
for file in $(find ./$1 -name "*.gz"); do
  # use make_name.sh to get the name
  name=$(bash -C ./scripts/get_name.sh $1 $file)
  # name=$(echo $name | tr '[:lower:]' '[:upper:]')
  
  $(bash -C ./scripts/use_xxd.sh $file $name $2)
done

# put favicon.ico if it exists as binary data
if [ -f ./$1/favicon.ico ]; then
  $(bash -C ./scripts/use_xxd.sh ./$1/favicon.ico favicon_ico $2)
fi
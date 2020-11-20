#!/bin/bash

var1=$1
son=0
father=0
while [ $var1 -gt 0 ]
do
  if [ "$(./a.out)" = "#" ]
    then
      let "father+=1"
    else
      let "son+=1"
  fi
  var1=$[ $var1 - 1 ]
done
echo "son:" $son "father:" $father

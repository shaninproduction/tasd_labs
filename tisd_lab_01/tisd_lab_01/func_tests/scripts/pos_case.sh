#!/bin/bash

if [ -z $1 -o -z $2 ]; then
    exit 1
fi

cd ../..

./app.exe < $1 > "./temp_out"

if [[ $? != 0 ]]; then
    exit 1
fi

./func_tests/scripts/comparator_nums.sh ./temp_out $2

if [[ $? =~ 0 ]]; then
    rm "./temp_out"
    exit 0
else
rm "./temp_out"
    exit 1
fi 

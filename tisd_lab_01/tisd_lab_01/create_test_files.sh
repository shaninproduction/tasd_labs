#!/bin/bash

if [ -z $1 -o -z $2 ]; then
    exit 1
fi

for ((i = 1; i <= $2; i++))
{
    if [ $1 = "pos" ]; then

        if [ $i -lt 10 ]; then
            touch ./func_tests/data/pos_0${i}_in.txt
            touch ./func_tests/data/pos_0${i}_out.txt
        else
            touch ./func_tests/data/pos_${i}_in.txt
            touch ./func_tests/data/pos_${i}_out.txt
        fi
    fi

    if [ $1 = "neg" ]; then

        if [ $i -lt 10 ]; then
            touch ./func_tests/data/neg_0${i}_in.txt
        else
            touch ./func_tests/data/neg_${i}_in.txt
        fi
    fi
}
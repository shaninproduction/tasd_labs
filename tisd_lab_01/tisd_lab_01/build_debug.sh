#!/bin/bash

if [ ! -f ./main.c ]; then
    echo Error: No main.c file.
    exit 1
fi 

gcc -c -O0 -g3 $(ls . | grep .c$)
gcc $(ls . | grep .o$) -o app.exe
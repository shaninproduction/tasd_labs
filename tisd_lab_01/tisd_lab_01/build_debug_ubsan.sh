#!/bin/bash

if [ ! -f ./main.c ]; then
    echo Error: No main.c file.
    exit 1
fi 

clang -fsanitize=undefined -fno-omit-frame-pointer -c -O0 -g3 $(ls . | grep .c$)
clang -fsanitize=undefined -fno-omit-frame-pointer -g $(ls . | grep .c$) -o app.exe

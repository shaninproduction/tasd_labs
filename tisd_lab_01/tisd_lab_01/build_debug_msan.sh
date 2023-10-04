#!/bin/bash

if [ ! -f ./main.c ]; then
    echo Error: No main.c file.
    exit 1
fi 

clang -fsanitize=memory -fno-omit-frame-pointer -c -O0 -g3 $(ls . | grep .c$)
clang -fsanitize=memory -fno-omit-frame-pointer -g $(ls . | grep .o$) -o app.exe
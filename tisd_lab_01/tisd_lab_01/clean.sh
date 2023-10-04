#!/bin/bash

# Скрипт для удаления побочных файлов

list=$(ls | egrep "\.exe$|\.o$|^temp_out$")
if [[ $list == "" ]]; then
    echo "Нет побочных файлов."
else
    echo "Побочные файлы удалены"
    rm $list
fi

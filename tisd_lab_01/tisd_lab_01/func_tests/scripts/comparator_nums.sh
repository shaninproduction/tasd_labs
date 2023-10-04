#/bin/bash
if [ -z "$1" -o -z "$2" ]; then
	exit 1

else
touch file1 file2
reg="Результат: "
flag=false
while read -r line; do

    if [[ $flag = true ]]; then
            echo $line >> file1

    else
    
        if [[ $line =~ $reg ]]; then
            flag=true
            temp=${line#*$reg}
            echo $temp > file1
        fi
        

    fi    
done < $1

flag=false
while read -r line; do

    if [[ $flag = true ]]; then
            echo $line >> file2

    else
    
        if [[ $line =~ $reg ]]; then
            flag=true
            temp=${line#*$reg}
            echo $temp > file2
        fi
        

    fi    
done < $2

if cmp -s file1 file2; then 
		rm file1 file2
		exit 0 
	else
		rm file1 file2
		exit 1 
	fi

fi

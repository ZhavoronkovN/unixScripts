#!/usr/bin/bash
if [[ "$1" = "-h" || "$2" = "-h" ]] 
then
	echo "Task 1. Write directory, file type and it will delete all files in directory of that type"
	exit 0
fi
if [[ ! "$1" || ! "$2" ]]
then
        echo "Too few arguments. Type -h for help"
        exit 1
fi
if [[ "$1" && "$2" && "$3" ]]
then
        echo "Too much arguments. Type -h for help"
	exit 2
fi
cd $1
for dir in */
do
	cd $dir
	for file in *
	do
		if [[ -w $file && "${file##*.}" = "$2" ]] 
		then
			rm $file
		fi
	done
	cd
done

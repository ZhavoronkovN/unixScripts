#!/usr/bin/bash

if [[ "$1" = "-h" || "$2" = "-h" ]]
then
	echo "Task 2. Write directory and file type, and it will delete all files with the same name in that directory, except that have the type you wrote"
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
for file1 in *
do
	for file2 in *
	do
		if [[ ${file1%%*.} = ${file2%%*.} && $file1 != $file2 ]]
		then
			if [[ ${file2##*.} != $2 ]]
			then
				rm $file2
			fi
		fi
	done
	if [[ ${file1##*.} != $2 ]]
	then
		rm $file1
	fi
done

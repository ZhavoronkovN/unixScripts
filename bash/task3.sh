#!/bin/bash

if [[ "$1" = "-h" ]]
then
	echo "Task 3. Prints files that was modified less than hour ago. Prints 10 the oldest files. Copies 10 new to directory backup"
	exit 0
elif [[ "$1" ]]
then
	echo "Too much arguments. Type -h for help"
	exit 1
fi
cd
for file in $(find -not -path '*/\.*' -type f -mmin -60)
do
	echo $file
done
cnt=0
size=0
for file in $(find -not -path '*/\.*' -type f -ls | sort -k8M -k9 -k10|awk '{print $11}')
do
	if [[ cnt -lt 10 ]]
	then
		let "cnt = cnt + 1"
		echo $(ls -l $file)
		let "size = size + $(stat -c%s $file)"
	fi
done
echo $size
cnt=0
mkdir -p backup
for file in $(find -not -path '*/\.*' -type f -ls | sort -r -k8M -k9 -k10|awk '{print $11}')
do
	if [[ cnt -lt 10 ]]
	then
		let "cnt = cnt + 1"
		cp $file backup
	fi
done

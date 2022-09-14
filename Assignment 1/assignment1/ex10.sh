#!/bin/bash

# Filename: ex10.sh
#
# Problem: Use a loop to count from 1 to 10


count=1

while [ $count -le 10 ]
do
	echo Count is: $count
	count=$(($count + 1))
done


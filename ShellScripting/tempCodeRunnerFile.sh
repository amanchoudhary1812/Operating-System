#!/bin/bash

# Input a number
echo "Enter a number: "
read number

# Check if the number is positive or negative
if [ $number -gt 0 ]; then
    echo "The number is positive."
elif [ $number -lt 0 ]; then
    echo "The number is negative."
else
    echo "The number is zero."
fi


#!/bin/bash
num=1
until [ $num -gt 5 ]  # Fixed spacing issue
do
    echo "number: value of $num"
    ((num++))
done

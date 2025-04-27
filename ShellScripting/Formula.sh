#!/bin/bash

echo "Squares of numbers from 1 to 5:"

for (( i=1; i<=5; i++ ))
do
  square=$(( i * i ))
  echo "$i squared is $square"
done

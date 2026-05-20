#!/bin/bash

echo "Enter a number:"
read num

if [ "$num" -lt 0 ]; then
    echo "Error: Factorial of a negative number is not defined."
    exit 1
fi

fact=1

for (( i=1; i<=num; i++ ))
do
    fact=$((fact * i))
done

echo "Factorial of $num is $fact"


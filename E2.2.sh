#!/bin/bash

secret=$(( RANDOM % 20 + 1 ))
attempts=0
guess=0

echo "Guess a number between 1 and 20"

while [ "$guess" -ne "$secret" ]
do
    read guess
    attempts=$((attempts + 1))

    if [ "$guess" -gt "$secret" ]; then
        echo "Too high!"
    elif [ "$guess" -lt "$secret" ]; then
        echo "Too low!"
    fi
done

echo "Success! The number was $secret"
echo "Attempts taken: $attempts"


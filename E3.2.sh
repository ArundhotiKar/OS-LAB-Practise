#!/bin/bash

if [ -z "$1" ]; then
    echo "Usage: $0 <filename>"
    exit 1
fi

file="$1"

while true
do
    if [ ! -e "$file" ]; then
        msg="$(date '+%Y-%m-%d %H:%M:%S') ERROR: File '$file' does not exist"
        echo "$msg" >&2
        echo "$msg" >> error.log
    else
        echo "File is safe"
    fi

    sleep 5
done


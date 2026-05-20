#!/bin/bash

# Check if a filename was provided as a command-line argument
if [ $# -eq 0 ]; then
    echo "Error: No filename provided"
    exit 1
fi

# Get the filename/path from the first argument
filename="$1"

# Check if the path exists
if [ -e "$filename" ]; then
    if [ -f "$filename" ]; then
        # It's a file, check if writable
        if [ -w "$filename" ]; then
            echo "File exists and is writable"
        else
            echo "File exists but is read-only"
        fi
    elif [ -d "$filename" ]; then
        # It's a directory
        echo "This is a directory"
    else
        # Exists but not a regular file or directory
        echo "Path exists but is not a regular file or directory"
    fi
else
    # Path doesn't exist
    echo "Path does not exist"
fi
.sh

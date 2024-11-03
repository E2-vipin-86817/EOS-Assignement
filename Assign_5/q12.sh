#!/bin/bash

# Check if a filename is provided as an argument
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <filename>"
    exit 1
fi

filename="$1"

# Check if the file exists
if [ -f "$filename" ]; then
    # Display the last modification time of the file
    mod_time=$(stat -c %y "$filename")
    echo "The last modification time of '$filename' is: $mod_time"
else
    # Display a message if the file does not exist
    echo "File '$filename' does not exist."
fi

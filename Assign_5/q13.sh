#!/bin/bash

# Display only hidden files in the current directory
echo "Hidden files in the current directory:"
ls -d .[^.]* 2>/dev/null

# Check if there are no hidden files
if [ $? -ne 0 ]; then
    echo "No hidden files found."
fi

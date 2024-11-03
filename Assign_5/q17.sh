#!/bin/bash

# Number of rows for the pattern
rows=5

# Loop to print the pattern
for ((i=1; i<=rows; i++)); do
    # Print i asterisks followed by a space
    for ((j=1; j<=i; j++)); do
        echo -n "* "
    done
    # Move to the next line after each row
    echo
done

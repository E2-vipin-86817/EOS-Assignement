#!/bin/bash

# Function to generate Fibonacci series
fibonacci() {
    local terms=$1
    local a=0
    local b=1

    echo "Fibonacci Series up to $terms terms:"

    for ((i=0; i<terms; i++)); do
        echo -n "$a "
        # Calculate next term
        local next=$((a + b))
        a=$b
        b=$next
    done

    echo # Print a new line at the end
}

# Prompt the user to enter the number of terms
read -p "Enter the number of terms in the Fibonacci series: " number

# Check if the input is a valid positive integer
if ! [[ "$number" =~ ^[0-9]+$ ]]; then
    echo "Invalid input. Please enter a valid positive integer."
    exit 1
fi

# Call the function to generate Fibonacci series
fibonacci "$number"

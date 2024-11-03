#!/bin/bash

# Prompt the user to enter a number
read -p "Enter a number to print its multiplication table: " number

# Check if the input is a valid number
if ! [[ "$number" =~ ^-?[0-9]+$ ]]; then
    echo "Invalid input. Please enter a valid integer."
    exit 1
fi

# Print the multiplication table
echo "Multiplication Table of $number:"
for ((i=1; i<=10; i++)); do
    result=$((number * i))
    echo "$number x $i = $result"
done

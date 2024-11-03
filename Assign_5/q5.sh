#!/bin/bash

# Prompt the user to enter three numbers
read -p "Enter first number: " num1
read -p "Enter second number: " num2
read -p "Enter third number: " num3

# Initialize greatest variable
greatest=$num1

# Compare with the second number
if [ "$num2" -gt "$greatest" ]; then
    greatest=$num2
fi

# Compare with the third number
if [ "$num3" -gt "$greatest" ]; then
    greatest=$num3
fi

# Display the result
echo "The greatest number is: $greatest"

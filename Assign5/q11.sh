#!/bin/bash

# Prompt the user to enter the basic salary
read -p "Enter your basic salary: " basic_salary

# Check if the input is a valid number
if ! [[ "$basic_salary" =~ ^[0-9]+([.][0-9]+)?$ ]]; then
    echo "Invalid input. Please enter a valid numeric value for basic salary."
    exit 1
fi

# Calculate DA and HRA
da=$(echo "$basic_salary * 0.40" | bc)
hra=$(echo "$basic_salary * 0.20" | bc)

# Calculate gross salary
gross_salary=$(echo "$basic_salary + $da + $hra" | bc)

# Display the result
printf "Gross Salary: %.2f\n" "$gross_salary"

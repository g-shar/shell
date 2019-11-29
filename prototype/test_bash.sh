#!/bin/sh

# Variable declaration
var1=('(echo A)')
#var2=("ls -a)
#var3=("git branch")

# Executes & runs command, stores result in input1
input1=$(${var1})

# Displays input1
echo "Input 1 ran: $input1"

# Runs commands through test_bash & stores to output
echo $(./test_bash \' ${var1} \') > 'output.txt'

# Grabs text from output.txt & stores to output1
output1=$(cat output.txt)


echo "System Call: $input1"
echo "Test Bash Call: $output1"


if [ "$output1" = "$input1" ]
then
	echo "Success"

else
	echo "Fails"
fi




#!/bin/sh

TESTS=( "\"(echo A && echo B) || (echo C && echo D)\"" "\"(echo  A || echo B) && echo A\"" "\"echo A && ((echo B || echo C) &&  echo D)\"")

for input in "${TESTS[@]}"
do
   echo "Precedence Test with ${input}"
   $(../rshell ${input}) > integration_tests.txt
   input2=$(eval ${input}) 
   output=$(cat integration_tests.txt)
   echo "System: $input2"
   echo "Rshell: $output"
   if [ "$input2" = "$output" ]
   then
	echo "Precedence test succeeded with ${input}"
   else
	echo "Precedence test failed with ${input}"
   fi
   echo " "
done



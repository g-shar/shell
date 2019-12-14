#!/bin/sh

TESTS=( "echo hello < integration_tests.txt; cat < integration_tests.txt | tr A-Z a-z && ls -a" "eho no || ls -a | tr a-z A-Z && echo \"success\"")

for input in "${TESTS[@]}"
do
   echo "PipingOperator Test with ${input}"
   echo $(./rshell ${input})
   EXECUTION=$?
   if [ $EXECUTION -eq 0 ];
   then
      echo "A command was executed" 
   else
      echo "${input} failed and was not executed"
      exit 1
   fi
   
   input1=$(${input})
   output=$(cat integration_tests.txt)
   echo "system: $input1"
   echo "rshell: $output"
done

#tests primarily for piping operations

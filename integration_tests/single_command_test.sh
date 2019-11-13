#!/bin/sh

INPUTS=( "echo \"hello\""  "ls -a" "mkdir test")

for input in "${INPUTS[@]}"
do
   echo "SingleCommandExecutions test with ${input}"
   ./rshell ${input} > integration_tests
   EXECUTION=$?
   if [ $EXECUTION -eq 0 ];
   then
      echo "A command was executed" 
   else
      echo "${input} failed and was not executed"
      exit 1
   fi
   
   input1=$(${input})
   echo "Checking if correct execution of command..."
   if [ "$output" == "$input1" ]
   then 
      echo "Single Command Execution test passed with ${input}"
   else 
      echo "Single Command Execution test failed with ${input}"
   fi
done

#tests primarily for command executions

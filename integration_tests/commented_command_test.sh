#!/bin/sh

TESTS=("ls #-a" "echo yes #&& git status" "git branch #newBranch;" )

for input in "${TESTS[@]}"
do
   echo "CommentedCommands test with ${input}"
   echo $(./../rshell ${input}) > integration_tests.txt
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
   echo "Checking if correct execution of command..."
   if [ "$output"= "$input1" ]
   then 
      echo "Command with Comments Execution test passed with ${input}"
   else 
      echo "Command with Comments Execution test failed with ${input}"
   fi
done

#tests primarily for comments being respected

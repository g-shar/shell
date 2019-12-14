#!/bin/sh

TESTS=( "cat < integration_tests.txt && echo \"second command executed\"" "ca < integration_tests.txt && ls -a")

for input in "${TESTS[@]}"
do
   echo ""
   echo "INPUT Redirection Test with ${input}"
   echo $(../rshell ${input})
   echo ""
   EXECUTION=$?
   if [ $EXECUTION -eq 0 ];
   then
      echo "A command was executed" 
   else
      echo "${input} failed and was not executed"
      exit 1
   fi
   
   output=$(cat integration_tests.txt)
   echo "CONTENTS OF \"integration_tests.txt\":"
   echo "$output"
done

#tests primarily for output redirection

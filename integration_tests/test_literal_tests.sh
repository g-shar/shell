#!/bin/sh

TESTS=("test -e ../unit_test" "test -f ../names.txt" "test -d ../integration_test")
TESTS2="echo hello"
for input in "${TESTS[@]}"
do
   echo "Testing with ${input} && echo \"executed\""
   echo " "
   rshell_result= $(../rshell {input})  &&  echo "executed" > integration_tests.txt 
   system_result=$(${input})	#runs the test command
   if [ "$?" -eq 0 ];	#if test  command is successful, then next command should be executed
   then
      system_result= "executed" 
   fi
   output=$(grep ^$system_result integration_tests.txt)
   echo "system: ${system_result}"
   echo "rshell: ${rshell_result}"
   if [ ! -z "$output" ]
   then 
      	echo "Test command execution test passed with ${input}"
   else 
      	echo "Test command execution test failed with ${input}"
   fi

   echo "Testing with || connectors..."
   rshell_result=$(../rshell ${input}) || echo "executed" > integration_tests.txt 
   system_result=$(${input})		#runs the test command
   if [ ! "$?" -eq 0 ];	#if test command is not successful, then next command should be executed
   then 
      system_result="executed"
   fi
   output=$(grep ^$system_result integration_tests.txt)
   echo "system: ${system_result}"
   echo "rshell: ${rshell_result}"
   echo "Checking if correct execution of command..."
   if [ ! -z "$output" ]
   then 
      	echo "Test command execution test passed with ${input}"
   else 
      	echo "Test command execution test failed with ${input}"
   fi 
done



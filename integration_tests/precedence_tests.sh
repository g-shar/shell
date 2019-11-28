#!/bin/sh

TESTS=("test -e ../unit_test" "test -f ../names.txt" "test -d ../integration_test")

for input in "${TESTS[@]}"
do
   echo "Test CMD Test starting..."
   echo $(../rshell ${input}) #> integration_tests.txt 
   $(${input})		#runs the test command
   if [ "$?" -eq 0 ];	#decides what output based on the success of the system test command
   then
      result="(True)"
   else
      result="(False)"
   fi
   output=$(grep ^$result integration_tests.txt)
   echo "system: ${result}"
   echo "rshell: ${output}"
   echo "Checking if correct execution of command..."
   if [ ! -z "$output" ]
   then 
      	echo "Test command execution test passed with ${input}"
   else 
      	echo "Test command execution test failed with ${input}"
   fi
done



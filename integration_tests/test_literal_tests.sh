#!/bin/sh

TESTS=("test -e ../unit_test" "test -f ../names.txt" "test -d ../integration_test")

for input in "${TESTS[@]}"
do
   echo "Testing connectors with \"${input}\""
   echo " "
   rshell_result= $(../rshell {input})  &&  echo "2nd_cmd_executed" > integration_tests.txt 
   system_result=$(${input})	#runs the test command
   if [ "$?" -eq 0 ];	#if test  command is successful, then next command should be executed
   then
      system_result="2nd_cmd_executed" 
   fi
   output=$(grep ^${system_result} integration_tests.txt)
   echo "system: ${system_result}"
   echo "rshell: ${output}"
   if [ ! -z "$output" ]
   then 
      	echo "TestCMD Test passed with \"${input} && echo 2nd_cmd_executed\""
   else 
      	echo "TestCMD Test failed with \"${input} && echo 2nd_cmd_executed\""
   fi
   echo " "

   echo "Testing with || connectors..."
   rshell_result=$(../rshell ${input}) || echo "2nd_cmd_executed" > integration_tests.txt 
   system_result=$(${input})		#runs the test command
   if [ ! "$?" -eq 0 ];	#if test command is not successful, then next command should be executed
   then 
      system_result="2nd_cmd_executed"
   fi
   output=$(grep ^$system_result integration_tests.txt)
   echo "system: ${system_result}"
   echo "rshell: ${output}"
   echo "Checking if correct execution of command..."
   if [ ! -z "$output" ]
   then 
      	echo "TestCMD Test passed with \"${input} || echo 2nd_cmd_executed\""
   else 
      	echo "TestCMD Test failed with \"${input} || echo 2nd_cmd_executed\""
   fi
   echo " "

   echo "Testing with ; connectors..."
   rshell_result=$(../rshell ${input}) ; echo "2nd_cmd_executed" > integration_tests.txt 
   system_result="2nd_cmd_executed"
   output=$(grep ^$system_result integration_tests.txt)
   echo "system: ${system_result}"
   echo "rshell: ${output}"
   echo "Checking if correct execution of command..."
   if [ ! -z "$output" ]
   then 
      	echo "TestCMD test passed with \"${input} ; echo 2nd_cmd_executed\""
   else 
      	echo "TestCMD test failed with \"${input} ; echo 2nd_cmd_executed\""
   fi
   echo " "
done



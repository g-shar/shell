# CS 100 RShell

# Project Information
Fall 2019 <br/>
Richard Duong <br/> 
Gregory Shar 862087118<br/>

# Introduction
This project is a command shell that prints a command prompt, reads in a line of commands and connectors from standard input, and executes the appropriate commands using fork, execvp, and waitpid. The program accomplishes this by first creating multiple command objects for each user-inputted command that each contain the executable in string form and an array of tje passed in arguments that have been parsed already. The program then uses a composite pattern to create a tree composed of these command objects and connector objects, with the command objects as the primitives and the connector objects as the composites. The program then traverses the tree, using a doWork() funciton in order to go through any input connectors and command objects to determine what commands should or should not be executed based on previous commands, and to execute the commands themselves.

# Diagram

# Classes

## Base_Cmd

Base_Cmd is the abstract base component class used to help form the part-whole hierarchy containing the composites (Connectors) and the primitives (Cmd_Obj). The hierarchy created allows the program to decide which commands to execute based on the user-inputted connectors and in what order to execute them.

## Cmd_Obj

Cmd_Obj contains a string with the executable and an array of parsed argument list strings. These two objects will both be used in the Cmd_Obj’s function implementation of doWork(), which will call execute() and will run the user-inputted command using execvp(), waitpid(), and fork(). Cmd_Obj also contains a parse() function that parses the input into the string executable and the array of argument list strings.

## Connectors

Connectors is the abstract base class with subclasses for each connector: “;” , “&&”, and “||”. Each subclass will contain a different implementation of the doWork() function that decides whether to execute the next command based on the previous command.

### Semicolon  
Implementation of doWork() will always allow the next command to execute

### And
Implementation of doWork() will allow the next command to execute if the previous command succeeded

### Or
Implementation of doWork() will allow the next command to execute if the previous command failed

# Protoypes/Research

Most of our findings for this test were mainly learning about how the main system functions work individually and also together. The tests helped to show how execvp terminates the child if it is successful, the importance of waitpid() and the different parameters the function takes, and how execvp does not treat the first element in the array as part of the argument list. 
```
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string>
#include <iostream>

int main()
{
  char* cmd="echo";
  char* argList[5];
  argList[0]="echo";
  argList[1]="hello";
  argList[2]="&&";
  argList[3]="goodbye";
  argList[4]=NULL;
  int status;

  pid_t pid;

  pid=fork();

  if(pid==0)		//if in the child
  {
    if(execvp(cmd, argList)<0)	//if there was an error in execvp()
    {
      perror("execvp issue");

    }
  }
  else if(pid==-1)		//if there was an error in forking
  {
    perror("forking issue");
    exit(1);
  }
  else if(pid>0)								//if in the parent
  {
    waitpid(-1, &status, 0);
    //std::cout<<"parent: "<<pid<<std::endl;
  }
  return 0;
}
```
  

# Development and Testing Roadmap
- [#2](https://github.com/cs100/assignment-windows-defender/issues/2) Create component class Base_Cmd 
- [#3](https://github.com/cs100/assignment-windows-defender/issues/3) Create mock classes and functions for Cmd_Obj and subclasses of Connectors
- [#4](https://github.com/cs100/assignment-windows-defender/issues/3) Create unit tests for implementation of doWork() in Semicolon
- [#5](https://github.com/cs100/assignment-windows-defender/issues/3) Create implementation of doWork() in Semicolon and run unit tests
- [#6](https://github.com/cs100/assignment-windows-defender/issues/3) Create and run integration tests of doWork() in Semicolon with type Cmd_Obj objects
- [#7](https://github.com/cs100/assignment-windows-defender/issues/3) Create unit tests of doWork() in And
- [#8](https://github.com/cs100/assignment-windows-defender/issues/3) Create implementation of doWork() in And and run unit tests
- [#9](https://github.com/cs100/assignment-windows-defender/issues/3) Test implementation of doWork() in And integrated with other objects Semicolon and Cmd_Obj
- [#10](https://github.com/cs100/assignment-windows-defender/issues/3) Create unit tests for doWork() in Or
- [#11](https://github.com/cs100/assignment-windows-defender/issues/3) Create implementation for doWork() in Or and run unit tests 
- [#12](https://github.com/cs100/assignment-windows-defender/issues/3) Test implementation of doWork() in Or integrated with other objects Semicolon, And, and Cmd_Obj
- [#13](https://github.com/cs100/assignment-windows-defender/issues/3) Create unit tests for parse() function
- [#14](https://github.com/cs100/assignment-windows-defender/issues/3) Create integration tests for parse() function and Connector classes
- [#15](https://github.com/cs100/assignment-windows-defender/issues/3) Create parse() function
- [#16](https://github.com/cs100/assignment-windows-defender/issues/3) Create unit tests for execute() function with different edge cases
- [#17](https://github.com/cs100/assignment-windows-defender/issues/3) Create integration tests for the execution of different commands with different connectors
- [#18](https://github.com/cs100/assignment-windows-defender/issues/3) Create execute() function in Cmd_Obj and run unit and integration tests



 





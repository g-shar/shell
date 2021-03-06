# CS 100 RShell

# Project Information
Fall 2019 <br/>
Richard Duong <br/> 
Gregory Shar 862087118<br/>

# Introduction
This project is a command shell that prints a command prompt, reads in a line of commands and connectors from standard input, and executes the appropriate commands using fork, execvp, and waitpid. The program accomplishes this by first creating multiple command objects for each user-inputted command that each contain the executable in string form and an array of tje passed in arguments that have been parsed already. The program then uses a composite pattern to create a tree composed of these command objects and connector objects, with the command objects as the primitives and the connector objects as the composites. The program then traverses the tree, using a doWork() funciton in order to go through any input connectors and command objects to determine what commands should or should not be executed based on previous commands, and to execute the commands themselves.

# Diagram
![RShell Diagram](https://user-images.githubusercontent.com/46507098/68909726-2ded2000-0704-11ea-928a-7237b4acd066.jpg)

# Classes

## Interface

The class Interface is used to encapsulate the program, and where the command is parsed in order to help form the part-whole hierarchy of Base_Cmd pointers. The interface also contains an execute command, which uses the tree formed from Connectors and Cmd_Obj to run all the commands and connectors inputted by the user.

## Base_Cmd

Base_Cmd is the abstract base component class used to help form the part-whole hierarchy containing the composites (Connectors) and the primitives (Cmd_Obj). The class also contains the pure virtual function doWork(), which has different implementations based on the derived class.

## Cmd_Obj

Cmd_Obj is a subclass of Base_Cmd. Cmd_Obj differs from Base_Cmd because it contains a string with the executable and an array of parsed argument list strings. These two objects will both be used in the Cmd_Obj’s function implementation of doWork(), which will run a single user-inputted command using execvp(), waitpid(), and fork().  

## Connectors

Connectors is the abstract base class with subclasses for each connector: “;” , “&&”, and “||”. Each subclass will contain a different implementation of the doWork() function that decides whether to execute the next command based on the previous command. Connectors differ from Cmd_Objs in that they are composed of 2 base_cmd pointers- a left and a right. These can take either other connectors, or leaf Cmd_Objs and work to traverse and implement their specified logic. If connectors connect to a leaf, they usually verify whether the Cmd_Obj was able to successfully execute through execvp() to determine their next course of action. If connectors connect to another connector, we continue to traverse through the tree until we hit the leafs and return gradually and executing based on returns of the doWork() functions.

* Class `Semicolon`: This class's implementation of doWork() will always allow the next command to execute. However semicolon does need to verify that the only arguments allowed next to it are command arguments or another semicolon.

* Class `And`: This class's implementation of doWork() will allow the next command to execute if the previous command succeeded. We initially check the left base pointer to see if it's doWork allowed it to fully execute the command. If it has completed it, then attempt to execute the right base pointer. This class must also verify that left and right cannot be another connector.

* Class `Or`: This class's implementation of doWork() in this class will allow the next command to execute if the previous command failed. We initially check the left base pointer to see if it's doWork allowed it to fully execute the command. If it hasn't completed it, then attempt to execute the right base pointer. This class must also verify that left and right cannot be another connector.

# Protoypes/Research


### System function research

Most of our findings for this test were mainly learning about how the main system functions work individually and also how they interacted with each other. The tests showed us how execvp terminates the child if it is successful, the importance of waitpid() and the different parameters it can take, and how execvp does not treat the first element in the array as part of the argument. We also found out that execvp() only returns if there is an error, in which case it returns -1. This is useful for when we implement this into our execute() function, because this functionality allows us to check for errors using perror().


```cpp

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

	if(pid==0)
	{
		if(execvp(cmd, argList)<0)
		{
			perror("execvp issue");
		}
	}
	else if(pid==-1)
	{
		perror("forking issue");
		exit(1);
	}

	else if(pid>0)
	{
		waitpid(-1, &status, 0);
	}

	return 0;
	
```

### Parsing research

We also did some preliminary testing on how the connectors act in different situations. Some things we noticed were that you are not able to chain connectors. The example "echo "hello" && ; echo "goodbye"" would not work, and has a syntax error. We also noticed how semicolons did not have to be included, which is important to take into consideration, especially when there is no connector at all ("echo "hello"" will work just fine with no connector). 

Our parse prototype function focused mainly on being able to separate and identify the differences between commands and connectors and be able to separate them into different buckets. There were different edge cases that had to be handled, such as consecutive whitespaces or handling quotation marks. There was also minor error handling such as a single ampersand or single pipe (_which will be corrected because they are valid connectors_). Our approach uses functions to filter but eventually will migrate into classes filtering and handling errors.


```
	
	// Parses cstring into appropriate bucket vectors prototype
	
	
	// Just to store commands & connectors
	vector<char*> commands, connectors;
	
	char* hold = NULL;	// Where cstring is copied to
	int length = 0;		// Used only for quote & cmd size
	int i = 0;		// Iterating value for the cstring

	while(phrase[i] != '\0'){

		// If a semicolon ;
		if(checkSemicolon(phrase + i) != NULL){
			length = 1;
			hold = newStrCpy(phrase + i, length);
			connectors.push_back(hold);
			i += length;
		}

		// If an AND ampersand &&
		else if(checkAnd(phrase + i) != NULL){
			length = 2;
			hold = newStrCpy(phrase + i, length);
			connectors.push_back(hold);
			i+=length;
		}
		
		// If an OR pipe ||
		else if(checkOr(phrase + i) != NULL){
			length = 2;
			hold = newStrCpy(phrase + i, length);
			connectors.push_back(hold);
			i += length ;
		}

		/* Needs separate implementation for matching single
		 * quotation marks */	

		// If has double quotation marks \"
		else if(checkQuotes(phrase + i) != NULL){
			int length = sizeQuote(phrase + i);
			hold = newStrCpy(phrase + i, length);
			commands.push_back(hold);
			i += length;
		}

		// If a space (commands & connectors ignore all whitespace)
		else if(checkSpace(phrase + i) != NULL){
			++i;
		}

		// If a command or argument
		else{
			int length = sizeCmd(phrase + i);
			hold = newStrCpy(phrase + i, length);
			commands.push_back(hold);
			i += length;
		}		
	}

	cout << endl << "Commands:" << endl << "-----" << endl;
	printVector(commands);

	cout << endl << "Connectors:" << endl << "-----" << endl;
	printVector(connectors);

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

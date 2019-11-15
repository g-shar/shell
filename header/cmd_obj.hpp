#ifndef __CMD_OBJ_HPP__
#define __CMD_OBJ_HPP__

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string>
#include <iostream>

#include "base_cmd.hpp"

class Cmd_Obj: public Base_Cmd {
public:
	Cmd_Obj(char* cmd){
		parse(cmd);		
	}

	Cmd_Obj(char* cmd, char* list[]): executable(cmd), argList(list){};

	~Cmd_Obj(){
		for(int i = 0; i < size; ++i)
		{
			delete[] argList[i];
		}
	}

	virtual bool doWork()
	{
		bool process=true;
	   	int status;
	   	pid_t pid;

	   	pid=fork();
	
		// Exit catch
		if(std::strstr(this->executable, "exit")){
			exit(1);	
		}

		else if(pid==0)
	   	{ 
			execvp(this->executable, this->argList);      
			perror("execvp");
			exit(1);
	   	}

	   	else if(pid==-1)
	   	{
			perror("fork");
			exit(1);
	   	}

	   	else
	   	{
			waitpid(-1, &status, 0);
	   	}

	   	if(WIFEXITED(status))
	   	{
		  	if(WEXITSTATUS(status)==0)
		  	{
				return true;
		  	}
		  	else
		  	{
			 	return false;
		  	}
	   	}
   		return false;
	}

	void printCommands(){
		for(int i = 0; i < size; ++i){
			cout << argList[i];
		}
	}

private:

	void parse(char* cmd){
		int i = 0;			// Counter for the command passed in
		int j = 0;			// Counter for the cstr arr
		int length = 0;		// For length determination
		vector<char*> vList;


		while(cmd[i] != '\0')
		{
			if(checkQuotes(cmd + i) != NULL)
			{
				length = sizeQuote(cmd + i);	
			}			

			else if(checkSpace(cmd + i) != NULL)
			{
				++i;
				continue;
			}

			else{
				length = sizeArg(cmd + i);
			}

			vList.push_back(Base_Cmd::newStrCpy(cmd + i, length));


			i += length;
			++j;
		}

		cmd = vList[0];
		size = j;
		argList = new char*[size + 1];		// account for null termination entry
		
		// set cstr arr to vector
		for(int k = 0; k < size; ++k){
			argList[k] = vList[k];
		}
		argList[size + 1] = "\0";
		executable = argList[0];

  	}

   	char* executable;
   	char** argList;
	int size;
};

#endif

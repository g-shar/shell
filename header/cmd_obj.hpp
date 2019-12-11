#ifndef __CMD_OBJ_HPP__
#define __CMD_OBJ_HPP__

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string>
#include <iostream>

#include "base_cmd.hpp"

class Cmd_Obj: public Base_Cmd {


public:
	Cmd_Obj(char* cmd): file_name(NULL){
		parse(cmd);		
	}

	Cmd_Obj(char* cmd, char* list[]): executable(cmd), argList(list), file_name(NULL){}
		int sz=0;
                while(argList[sz]!=NULL)
		{
			sz+=1;
		}
		this->size=sz;
	};

	~Cmd_Obj(){
		for(int i = 0; i < size; ++i)
		{
			delete[] argList[i];
		}
	}

	virtual bool doWork()
	{	
	   	int status;
	   	pid_t pid;
	   	pid=fork();
		// Exit catch
		if(std::strstr(this->executable, "exit")){
			exit(1);	
		}
		else if(pid==0)
	   	{
			if(std::strstr(this->executable, "test") || this->checkTest(this->argList, this->size))
			{
				//checks if test has a flag or a given path
				if(size>=2)
				{
					struct stat s1;
					//if test has a flag and a path
					if(size>=3)
					{	
						//checks if the file exists 
						if(stat(argList[2], &s1)==-1) 
						{
							cout<<"(False)"<<endl;
							exit(1);
						}
						//checks if test has a -f flag
						if(std::strstr(argList[1], "-f"))
						{
							//checks if the path is a regular file
							if(!(S_ISREG(s1.st_mode)))
							{	
								cout<<"(False)"<<endl;
								exit(1);
							}
							cout<<"(True)"<<endl;
							exit(0);				
						}
						//checks if test has a -d flag
						else if(std::strstr(argList[1], "-d"))
						{
							//checks if the path is a directory
							if(!(S_ISDIR(s1.st_mode)))
							{
								cout<<"(False)"<<endl;
								exit(1);
							}
							cout<<"(True)"<<endl;
							exit(0);
						}
						//if test has -e flag and the command runs successfully
						else if(std::strstr(argList[1], "-e"))
						{
							cout<<"(True)"<<endl;
							exit(0);
						}
						//returns false if it can't recognize the flag 
						cout<<"(False)"<<endl;
						exit(1);
					}
					//if test only has a path or only has a flag
					if(std::strstr(argList[1], "-e") || std::strstr(argList[1],"-d") || std::strstr(argList[1],"-f"))
					{
						cout<<"(True)"<<endl;
						exit(0);
					}
					if(stat(argList[1], &s1)==-1) 
					{
						cout<<"(False)"<<endl;
						exit(1);
					}
					cout<<"(True)"<<endl;
					exit(0);
					
				}
				cout<<"(False)"<<endl;
				exit(1);
			}
			else 
			{
				//cout<<"printing commands...:"<<this->executable<<" "<<argList[1]<<endl;
				//cout<<"execvp running..."; 
				execvp(this->executable, this->argList);      
				perror("execvp");
				exit(1);
			}

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

			vList.push_back(newStrCpy(cmd + i, length));


			i += length;
			++j;
		}

		size = j;
		argList = new char*[size + 1];		// account for null termination entry
		
		// set cstr arr to vector
		for(int k = 0; k < size; ++k){
			argList[k] = vList[k];
		}

		argList[size] = NULL;
		executable = argList[0];

  	}

	vector<cmd_obj*> pipes;
	char* file_name;
   	char* executable;
   	char** argList;
	int size;
};

#endif

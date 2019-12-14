// ucrRichard/parse_part1
#ifndef __CMD_OBJ_HPP__
#define __CMD_OBJ_HPP__

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string>
#include <iostream>

#include "base_cmd.hpp"

class Cmd_Obj: public Base_Cmd {


public:

	// Defaults to normal Cmd
	Cmd_Obj(char* cmd): file_name(NULL), type(en::CMD)
	{
		Cmd_Obj::parse(cmd);		
	}

	// For handling Special Cmd types 
	Cmd_Obj(char* cmd, char* file_name, en type): file_name(file_name), type(type)
	{
		Cmd_Obj::parse(cmd);
	}



	// Copy constructor just for vector
	Cmd_Obj(char* cmd, Cmd_Obj* copy, vector<Cmd_Obj*> list):list(list), type(copy->type)
	{
		file_name = handleCstr(copy->file_name);
		Cmd_Obj::parse(cmd);
		/*

		cout << endl << "Inside copy constructor!" << endl;
		cout << "This is the copy!" << endl;
		cout << "List size is: " << list.size() << endl;
		cout << "File name is: " << file_name << endl;
		cout << "Executable is: " << executable << endl;
		cout << "Size is: " << size << endl;
		*/
	}


	// Unit tests
	Cmd_Obj(char* cmd, char* list[]): executable(cmd), argList(list), file_name(NULL)
	{
		int sz = 0;
		while(argList[sz]!=NULL){
			sz+=1;
		}
		this->size=sz;
	}


	~Cmd_Obj()
	{
		for(int i = 0; i < size; ++i)
		{
			delete[] argList[i];
		}
	}


	// aight i'm tired of cstrings so
	static Cmd_Obj* getCmdObj(char* phrase)
	{
		string str = string(phrase);	// Cstring turned to string
		string cut = "";		// Substring cutting helper
		char* temp_cstr_cmd = NULL;
		Cmd_Obj* temp_cmd = NULL;
		vector<Cmd_Obj*> list;		// Vector keeping track of cmd_objs

		// If no pipes or redirects
		if(sizeRedirect(str) == str.size()){
			return new Cmd_Obj(phrase);
		}

		for(int i = 0; i < str.size(); ++i){

			// if pipe object
			if(str[i] == '|'){
				cut = str.substr(0, i);
				str = str.substr(i + 1);
				temp_cmd = getRedirect(cut);
				list.push_back(temp_cmd);	
			}


			if(!temp_cstr_cmd && cut != ""){
				temp_cstr_cmd = handleCstr(cut.c_str());
			}
		}


		// if still no character, it's a lonely redirect
		if(!temp_cstr_cmd){
			return getRedirect(str);
		}
		
		// closing commands

		// if there was any pipe, push last item onto vector
		// else don't use the vector at all
		else if(str != string(phrase)){
			temp_cmd = getRedirect(str);
			list.push_back(temp_cmd);
		}

		return new Cmd_Obj(temp_cstr_cmd, list[0], list);

	}

	static char* getLeftRedirect(const char* phrase){
		string line = trimWhitespace(string(phrase));
		int sign = sizeRedirect(line);
		string left_cmd = trimWhitespace(line.substr(0, sign));
		return handleCstr(left_cmd.c_str());
	}


	static Cmd_Obj* getRedirect(string phrase)
	{
		phrase = trimWhitespace(phrase);
		int next = sizeRedirect(phrase);
		string right_file;
		string left_cmd;
		char* file = NULL;
		char* cmd = NULL;

		// if normal command object
		if(next == string::npos){
			char* temp = handleCstr(phrase.c_str());
			return  new Cmd_Obj(temp);
		}

		// Turns left & right sides into cstrings
		right_file = trimWhitespace(phrase.substr(next + 1));
		left_cmd = trimWhitespace(phrase.substr(0, next));

		if(right_file[0] == '>'){
			right_file = right_file.substr(1);
		}

		file = handleCstr(right_file.c_str());
		cmd = handleCstr(left_cmd.c_str());
			

		// Handles which object return
		if(phrase[next] == '<'){
			/*
			cout << "cmd_obj.hpp INPUT OBJECT" << endl;
			cout << "file: " << file << endl;
			cout << "cmd: " << cmd << endl;
			*/
			return new Cmd_Obj(cmd, file, en::IN);
		}

		else if(phrase[next] == '>' && phrase[next+1] == '>'){
			/*
			cout << "cmd_obj.hpp APPEND OBJECT" << endl;
			cout << "file: " << file << endl;
			cout << "cmd: " << cmd << endl;
			*/
			return new Cmd_Obj(cmd, file, en::APP);
		}

		else if(phrase[next] == '>'){
			/*
			cout << "cmd_obj.hpp OUTPUT OBJECT" << endl;
			cout << "file: " << file << endl;
			cout << "cmd: " << cmd << endl;
			*/
			return new Cmd_Obj(cmd, file, en::OUT);
		}

		throw "Uncaught symbol? Base_cmd getRedirect();";
		exit(1);
	}


	void printCommands()
	{
		for(int i = 0; i < size; ++i){
			cout << argList[i];
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
			if(!list.empty())
			{	
				int stat;
				int pipes[this->list.size()-1*2];
				pipe(pipes);
				if (fork()==0)
				{
					dup2(pipes[1], 1);
					for(int i=0; i<(size-1)*2; ++i)
					{
						close(pipes[i]);
					}
					Cmd_Obj* temp= new Cmd_Obj(this->executable, this->argList);	//creates temp cmd_obj to ONLY run the command
					temp->doWork();
					delete temp;		
				}
				else
				{
					this->pipe_doWork(1, this->list.size(), pipes);
				}
				for(int i=0; i<size*2; ++i)
				{
					close(pipes[i]);
				}

				for(int i=0; i<size; ++i)
				{
					waitpid(-1, &stat, 0);
				}
					
			}
			else if(std::strstr(this->executable, "test") || this->checkTest(this->argList, this->size))
			{
				this->test_doWork();

			}
			else if(this->type!=en::CMD)
			{				
				this->io_doWork();	
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

private:

	void parse(char* cmd)
	{
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

		/*
		cout << endl << "Inside cmd_obj::parse" << endl;
		cout << "Executable: " << executable << endl;
		cout << "End cmd_obj::parse" << endl;
		*/

  	}

	void io_doWork()
	{
		if(this->type==en::IN)
		{
			int newin=open("filename", O_RDONLY);
			//int dupin=dup(0);
			dup2(newin, 0);
			close(newin);
			execvp(this->executable, this->argList);	
		}
		else if(this->type==en::OUT)
		{
			int newout=open("FILENAME", O_WRONLY);
			dup2(newout,1);
			close(newout);
			execvp(this->executable,this->argList);
		}
		else 
		{
			int newout2=open("FILENAME", O_WRONLY, O_APPEND);
			dup2(newout2, 1);	
			close(newout2);
			execvp(this->executable, this->argList);
		}
		
	}

	void test_doWork()
	{
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

	void pipe_doWork(int argIndex, int size, int pipes[])
	{
		if(argIndex<size)
		{
			pipe(pipes+(argIndex*2));
			if( fork() ==0)
			{
				dup2(pipes[(argIndex-1)*2], 0);
				dup2(pipes[argIndex*2+1], 1);

				for(int i=0; i<size*2; ++i)
				{
					close(pipes[i]);
				}
				
				list.at(argIndex)->doWork();
			}
			else
			{
				pipe_doWork(argIndex+1, size, pipes);	
			}
		}
		else
		{
			if(fork()==0)
			{
				dup2(pipes[(size-1)*2-2], 0);
				for(int i=0; i<size*2; ++i)
				{
					close(pipes[i]);
				}
				list.at(size-1)->doWork();
			}
		}
	}

	vector<Cmd_Obj*> list;
	char* file_name;
   	char* executable;
   	char** argList;
	int size;
	en type;
};

#endif

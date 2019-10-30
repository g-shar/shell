#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string>
#include <iostream>
using namespace std;


void process_child(){

}

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
}


/**************************************************************************************************************
 * Notes: 
 * pID = 0 is a child, it executes first 
 * pID > 0 is a parent, usually needs to wait for the child		
 * else pID fails
 *
 *
 * fork(): 
 * 		returns pID integer
 * 	    creates a parent process duplicate
 *
 * execvp(const char* cmd, const char* arg_list[])):
 * 		takes a const char* command, and an arg_list (command has to be index 0 in the arg_list) 
 * 		returns -1 if command doesn't execute
 * 		runs command on system
 *
 * 	waitpid(pid_t pid, int *statusPtr, int options):
 * 		pid => process id that the calling process needs to wait for
 *			   pid > 0: 	waits for process specified by id
 *			   pid == 0: 	waits for group ID
 *			   pid == -1:	waits for any child process
 *			   pid < -1:	waits for group ID equal to absolute value of pID
 *
 *		*statusPtr => not important right now (status of process can be checked with other functions on statusPtr)
 *
 *		options => not important right now (bitflag that determines when status information is returned)
 *
 *************************************************************************************************************/

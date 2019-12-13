#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string>
#include <vector>
#include <fcntl.h>
#include <iostream>
using namespace std;

/*
    Piping Test Code
 
*/
int main(int argc, char **argv)
{
    int status;
    int i;

	char* arg1[] = {"cat", "pipe_test.cpp", NULL};
	char* arg2[] = {"cat", NULL};
	char* arg3[] = {"tr", "a-z", "A-Z", NULL};
    
    //size is # of arguments in the vector or list
    //index starts at 0;
    
	/*
    char *arg1[] = {"cat", "scores", NULL};
    char *arg2[] = {"grep", "Villanova", NULL};
    char *arg3[] = {"cut", "-b", "1-10", NULL};
	*/
    
    // make 2 pipes (cat to grep and grep to cut); each has 2 fds
    
    // cmd1 | cmd2    (size: 2, pipe array: 2)
    // cmd1 | cmd2 | cmd3   (size: 3, pipe array: 4)
    // cmd1 | cmd2 | cmd3 | cmd4   (size: 4, pipe array: 6)



    int pipes[(size-1)*2];
    pipe(pipes); // sets up 1st pipe
    
    if (fork() == 0)
    {
        // replace cat's stdout with write part of 1st pipe
        
        dup2(pipes[1], 1);
        
        for(int i=0; i<(size-1)*2; ++i)
        {
            close(pipes[i]);
        }
        
        //runs command
        execvp(arg.at(0), arg1.at(0));
      	perror("execvp");
    }
    else
    {
        // calls pipe that forks
        pipe(1, int size);
        
    }
    
    // only the parent gets here and waits for 3 children to finish
    
    for(int i=0; i<size*2; ++i)
    {
        close(pipes[i]);
    }
    
    for (i = 0; i < 3; i++)
    {
      wait(&status);
    }
        
}


void pipe(int argIndex, int size) //argIndex=1 for second child, argIndex=2 for third child
{
    
    if(index+1!=size)
    {
        pipes(pipes+(argIndex*2));
        if (fork() == 0)
        {
            // replace  stdin with read end of 1st pipe
            
            dup2(pipes[(argIndex-1)*2], 0); //0, 2, 4
            
            // replace stdout with write end of 2nd pipe
            
            dup2(pipes[argIndex*2+1], 1);   //3, 5, 7
            
            // closes all ends of pipes
            
            for(int i=0; i<size*2; ++i)
            {
                close(pipes[i]);
            }
            
            execvp(*grep_args, grep_args);
          	perror("execvp");
        }
        else
        {
            pipe(vector.at(argIndex+1), size);  //goes to next command in vector or list; PSEUDOCODE
        }
    }
    else    //last command
    {
        if(fork()==0)
        {
            //replaces stdin with input read
            dup2(pipes[(size-1)*2-2], 0); //size-2 should be the last stdin for the pipes;
            
            for(int i=0; i<size*2; ++i)	//close all pipes
            {
                close(pipes[i]);
            }
            
            execvp(*args[size-1], args[size-1]);	//run the last command
          	perror("execvp");
        }
    }
    
}

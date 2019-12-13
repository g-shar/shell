#include <iostream>
using namespace std;


// Single Pipe
int main(){
	


	char*[] lhs = {"cat", "test1", NULL};
	char*[] rhs = {"cat", NULL};



	int file_desc[2];		// holds file_descriptor Process ID
	pipe(file_desc);	    // Creates a pipe based on what the ID is (always in pairs of integers)

	// Child Process (should handle reading or piped reading (RIGHT HAND SIDE))
	if(fork() == 0){
	
		dup2(file_desc[1], 1);			// puts stdinput into the pipe
		close(file_desc[0]);			// close the stdoutput FD

		execvp(rhs[0], rhs);			// runs the command

	}

	// Parent Process
	else{
		dup2(fil_desc[0], 0);			// puts stdoutput into the pipe
		close(file_desc[1]);			// close the stdinput PD

		execvp(lhs[0], lhs);			// runs the command
	}












}

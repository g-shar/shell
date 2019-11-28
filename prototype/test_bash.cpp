#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string>
#include <iostream>
using namespace std;

int main(int argv, char** argc){

	// argc[argv] = NULL;
	/*
	for(int i = 0; argc[i] != "\0" || argc[i] != NULL; ++i){
		cout << "Argument: " << i << " => " <<  argc[i] << endl;
	}
	*/

	execvp(argc[1], argc + 1);
}



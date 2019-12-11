#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string>
#include <iostream>
using namespace std;

int main(int argv, char** argc){

	// C-string of items piped
	char **args = argc + 1;

	// Arg count
	int arg_count = argv - 1;

	/*
	 * FOR TESTING
	cout << "Arg number: " << arg_count << endl;
	for(int i = 0; i < argv; ++i){	
		cout << args[i] << endl;
	}
	*/
}



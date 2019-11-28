#include "../header/interface.hpp"
#include <limits>
#include <iostream>

using namespace std;

void print(int argv, char** argc){
	for(int i = 0; i < argv; ++i){
		cout << i << " => " << argc[i] << endl;
	}
}

int main(int argv, char** argc){



	char* cmd = "echo hi && echo hi";
	char* arg_alt[] = {"./rshell_int", "echo", "hi", "&&", "echo", "hi"};

	/*
	cout << "custom line args" << endl;
	print(4, arg_alt);
	cout << "cmd line args" << endl;
	print(argv, argc);
	*/


	Interface rshell_cmd;

	cout << "First command: " << endl;
	rshell_cmd.setCommand(argv, arg_alt);
	rshell_cmd.doWork();

	cout << "Second command: " << endl;
	rshell_cmd.setCommand(argv, argc);
	rshell_cmd.doWork();

	/*
	cout << "Third command: " << endl;
	rshell_cmd.setCommand(cmd);
	*/


//	rshell_cmd.doWork();
}


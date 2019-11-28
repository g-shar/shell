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



	char* cmd = "echo hello world";
	char* arg_alt[] = {"./rshell_int", "echo", "hello", "world", NULL};

	/*
	cout << "custom line args" << endl;
	print(4, arg_alt);
	cout << "cmd line args" << endl;
	print(argv, argc);
	*/


	Interface rshell_cmd;
	Interface rshell_cstr;

	argc[argv + 1] = NULL;


	rshell_cmd.setCommand(argv, argc);
//	rshell_cmd.setCommand(argv, arg_alt);
//	rshell_cstr.setCommand(cmd);
	rshell_cmd.doWork();
}


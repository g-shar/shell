#include "../header/interface.hpp"
#include <limits>
#include <iostream>

using namespace std;

int main(int argv, char** argc){
	Interface rshell;

	char* NT = '\0';

	argc[argv] = NT;
	rshell.setCommand(argv, argc + 1);
	rshell.doWork();
}


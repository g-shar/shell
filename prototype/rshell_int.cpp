#include "../header/interface.hpp"
#include <limits>
#include <iostream>

using namespace std;

int main(int argv, char** argc){
	Interface rshell;
	argc[argv + 1] = NULL;
	rshell.setCommand(argv, argc + 1);
	rshell.doWork();
}


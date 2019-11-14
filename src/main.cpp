#include "../header/interface.hpp"
using namespace std;

const int MAX_CMD = 11;
int main(){

	char* text[MAX_CMD];
	text[0] = "git clone https://github.com/cs100/assignment-windows-defender.git";
	text[1] = "cd assignment-windows-defender";
	text[2] = "git checkout tags/hw2";
	text[3] = "git submodule init";
	text[4] = "git submodule update";
	text[5] = "cmake3 .";
	text[6] = "make";
	text[7] = "test -e rshell || echo \"rshell executable missing, check submission instruction\
	  	   section of the specifications\"";
	text[8] = "test -e test || echo \"test executable missing, check submission instruction\
	  	   section of the specifications\"";
	text[9] = "test -d unit_tests || echo \"unit_tests/ directory missing, check submission instruction\
	  		section of the specifications\"";
	text[10] = "test -d integration_tests || echo \"integration_tests/ directory missing, check submission\
					instruction section of the specifications\"";

	Interface test;
	for(int i = 0; i < MAX_CMD; ++i){ 
		test.setCommand(text[i]);
		test.doWork();
	}
}

#include "interface.hpp"
using namespace std;

int main(){
	char* text0 = "echo hello";
	char* text1 = "git clone https://github.com/cs100/assignment-windows-defender.git";
	char* text2 = "cd assignment-windows-defender";
	char* text3 = "git checkout tags/hw2";
	char* text4 = "git submodule init";
	char* text5 = "git submodule update";
	char* text6 = "cmake3 .";
	char* text7 = "make";
	char* text8 = "test -e rshell || echo \"rshell executable missing, check submission instruction\
				   section of the specifications\"";
	char* text9 = "test -e test || echo \"test executable missing, check submission instruction\
				   section of the specifications\"";
	char* text10 = "test -d unit_tests || echo \"unit_tests/ directory missing, check submission instruction\
					section of the specifications\"";
	char* text11 = "test -d integration_tests || echo \"integration_tests/ directory missing, check submission\
					instruction section of the specifications\"";

	Interface test1(text0);
	test1.doWork();
}

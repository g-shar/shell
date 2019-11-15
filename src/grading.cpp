#include "../header/interface.hpp"
#include <iostream>

using namespace std;

const int ARR_SIZE = 12;

int main(){
	Interface rshell;
	char* argList[ARR_SIZE];

	// single command execution
	argList[0] = "echo hello";
	argList[1] = "ls -all";
	argList[2] = "git status";
	argList[3] = "git branch";

	// commands w/ operators
	argList[4] = "test -e not_a_real_file || echo \"failed to find file\"";
	argList[5] = "echo again && echo \"and again\" && echo \"and again\"";
	argList[6] = "ech but || git branch -r && echo \"remote branches\"";
	argList[7] = "echo no && echo way ; echo but";
	
	// commands w/ comments
	argList[8] = "echo but && echo not #&& echo \"this time\"";
	argList[9] = "ech# || echo \"failed to run?\"";

	// commands w/ exit
	argList[10] = "echo \"fail to exit\" || exit now";
	argList[11] = "echo \"succeed to exit!\" ; exit";


	for(int i = 0; i < ARR_SIZE; ++i){
		rshell.setCommand(argList[i]);
		rshell.doWork();
	}


}

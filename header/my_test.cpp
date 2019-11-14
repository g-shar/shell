#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string>
#include <iostream>
using namespace std;

int main(){

	char* ex = "echo";
	char* argList[2];
	argList[0] = "echo";
	argList[1] = "there";

	execvp(ex, argList);

}



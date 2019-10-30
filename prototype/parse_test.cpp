#include <iostream>
#include <iomanip>
using namespace std;

int main(){
	char* test1 = "ls -all";
	char* test2 = "echo \"hello world\"";
	char* test3 = "echo hello && goodbye";
	char* test4 = "echo \"hello && goodbye\"";
	char* test5 = "ls;";
	char* test6 = "ls -a; echo hello && mkdir test || echo world; git status;";
	char* test7 = "cd";

}

char* handleQuotes(const char* phrase){

}



void parseDisplay(const char* phrase){
	for(int i = 0; phrase[i] != "\0"; ++i){
		
	}

}


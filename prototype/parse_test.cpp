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
	char* test8 = "";

}

char* checkSpace(const char* phrase){
	if(*phrase != " ")
	{
		return NULL;
	}
	return phrase;
}

char* checkSemicolon(const char* phrase){
	if(*phrase != ";")
	{
		return NULL;
	}
	return phrase;
}

char* checkAnd(const char* phrase){
	if(phrase[0] != "&" && phrase[1] != "&")
	{
		return NULL;
	}

	// skips forward?
	return phrase + 1;
}

char* checkOr(const char* phrase){
	if(phrase[0] != "|" && phrase[1] != "|")
	{
		return NULL;
	}	
	return phrase + 1;
}

char* checkQuotes(const char* phrase){
	if(phrase[0] == "\"")
	{
		for(int i = 1; phrase[i] != "\0"; ++i){
			if(phrase[i] == "\"")
			{
				return phrase + i;
			}
		}
		
		//	error from unfinished quote
		exit(1);
	}

	return NULL;
}




void parseDisplay(const char* phrase){
	

	for(int i = 0; phrase[i] != "\0"; ++i){
				
	}

}


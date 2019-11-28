#include "../header/interface.hpp"
#include <limits>
#include <iostream>

using namespace std;

int main(int argv, char** argc){
	Interface rshell;
	char cstr[100];
	
	try{
		if(argv == 1){
			while(true){
				cout << "$ ";
				cin.getline(cstr, sizeof(cstr), '\n');

				cstr[strlen(cstr)] = '\0';

				rshell.setCommand(cstr);
				rshell.doWork();
			}
		}
		else{
			rshell.setCommand(argv, argc);
			rshell.doWork();
		}
	}
	catch(const char* error){
		cout << error;
	}	
}


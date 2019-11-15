#include "../header/interface.hpp"
#include <limits>
#include <iostream>

using namespace std;

int main(){
	Interface rshell;
	char cstr[100] = {};
	while(true){

		try{
			cout << "$ ";
			cin.getline(cstr, sizeof(cstr), '\n');
		
			rshell.setCommand(cstr);
			rshell.doWork();
		}
		catch(const char* error){
			cout << error;
		}
	}
}


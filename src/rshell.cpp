#include "../header/interface.hpp"
#include <limits>
#include <iostream>

using namespace std;

const int MAX_CMD = 11;


int main(){
	Interface menu;
	char cstr[300] = {};
	while(true){

		cout << "$ ";
		cin.getline(cstr, sizeof(cstr), '\n');
		
		menu.setCommand(cstr);
		menu.doWork();
	}
}


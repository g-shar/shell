#include <iostream>
#include <string>

#include "base_cmd.hpp"
using namespace std;

int main(){
	string test1 = " test file ";
	cout << Base_Cmd::trimWhitespace(test1);
}

#include "interface.hpp"
using namespace std;

int main(){
	char* ctest1 = "mv home";
	char* ctest2 = "mv home ; echo hello";
	char* ctest3 = "mv home && echo hello && echo home";

	Interface test1 = Interface(ctest2);

}


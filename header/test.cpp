#include "interface.hpp"
using namespace std;

int main(){
	char* ctest1 = "mv home";
	char* ctest2 = "mv home ; echo hello";
	char* ctest3 = "mv home && echo hello && echo home";
	char* ctest4 = "mv home && echo hello || home";
	char* ctest5 = "mv home && echo hello || home;";

	Interface test1 = Interface(ctest1);
	Interface test2 = Interface(ctest2);
	Interface test3 = Interface(ctest3);
	Interface test4 = Interface(ctest4);
	// Interface test5 = Interface(ctest5);

}


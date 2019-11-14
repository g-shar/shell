#include "interface.hpp"
using namespace std;

int main(){
	char* ctest1 = "git clone ";
	char* ctest2 = "echo hello";
	char* ctest3 = "mv home && echo hello && echo home";
	char* ctest4 = "mv home && echo hello || home";
	char* ctest5 = "mv home && echo hello || home;";


	Cmd_Obj test = Cmd_Obj(ctest2);
	test.doWork();

}


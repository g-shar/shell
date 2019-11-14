#include "interface.hpp"
using namespace std;

int main(){
	char* text1 = "echo \"hello!\"";

	Interface test(text1);
	test->doWork();
}

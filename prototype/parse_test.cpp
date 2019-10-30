#include <iostream>
#include <iomanip>
#include <vector>
#include <cstring>
using namespace std;

char* checkSpace(char* phrase);
char* checkSemicolon(char* phrase);
char* checkAnd(char* phrase);
char* checkOr(char* phrase);
char* checkQuotes(char* phrase);
char* findEndQuote(char* phrase);
void parseToVectors(char* phrase);
void printVector(vector<char*> v);

int main(){
	char* test1 = "ls -all\0";
	char* test2 = "echo \"hello world\"";
	char* test3 = "echo hello && goodbye";
	char* test4 = "echo \"hello && goodbye\"";
	char* test5 = "ls;";
	char* test6 = "ls -a; echo hello && mkdir test || echo world; git status;";
	char* test7 = "cd";
	char* test8 = "";
	char* test9 = "ls    -a   ;";
	char* test10 = ";&&echo \'hello\';";
	char* test11 = ";||echo \'not home\'||echo \'is home\'";


	parseToVectors(test1);


}


/*************************
 * CHECK FUNCTIONS
 *************************/

char* checkSpace(char* phrase){
	if(*phrase == ' ')
	{
		return phrase;
	}
	return NULL;
}

char* checkSemicolon(char* phrase){
	if(*phrase == ';')
	{
		return phrase;
	}
	return NULL;
}

char* checkAnd(char* phrase){
	if(phrase[0] == '&' && phrase[1] == '&')
	{
		return phrase;
	}
	
	// Just one ampersand throws an error
	else if(phrase[0] == '&'){
		exit(1);
	}

	return NULL;
}

// Returns current pointer if it's an or
char* checkOr(char* phrase){
	if(phrase[0] != '|' && phrase[1] != '|')
	{
		return NULL;
	}	

	// Just one pipe throws an error
	else if(phrase[0] == '|'){
		exit(1);
	}
	return phrase;
}

// Returns current pointer if it's a quotation
char* checkQuotes(char* phrase){
	if(phrase[0] != '\"'){
		return NULL;
	}
	return phrase;
}

/*******************************
 *SPECIAL HELPER FUNCTIONS
 *******************************/


// Returns the end of the quotation or exits on error with no closing quote
char* findEndQuote(char* phrase){
	for(int i = 1; phrase[i] != '\0'; ++i){
		if(phrase[i] == '\"')
		{
			return phrase + i;
		}
	}
		
	//	error from unfinished quote
	exit(1);
	return NULL;
}


void parseToVectors(char* phrase){

	vector<char*> commands, connectors;

	char* temp = NULL;
	char* hold = NULL;
	int i = 0;

	while(phrase[i] != '\0'){
		cout << phrase[i];

		temp = checkQuotes(phrase + i);
		if(temp != NULL){
			//	distance from 2 pointers
			int length = temp - phrase - i;							 strncpy(phrase + i, hold, length);
			commands.push_back(hold);
		}

		else if(checkSemicolon(phrase + i) != NULL){
			strncpy(phrase + i, hold, 1);
			connectors.push_back(hold);
		}
		else if(checkAnd(phrase + i) != NULL){
			strncpy(phrase + i, hold, 2);
			connectors.push_back(hold);
		}
		else if(checkOr(phrase + i) != NULL){
			strncpy(phrase + i, hold, 2);
			connectors.push_back(hold);
		}
	
		// literally skips whitespace
		else if(checkSpace(phrase + i) == NULL){

		}		

		// Add this command to the vector
		else{

		}
		++i;
	}
	cout << endl << "Commands" << endl;
	printVector(commands);

	cout << endl << "Connectors" << endl;
	printVector(connectors);
}

void printVector(vector<char*> v){
	for(auto x: v){
		cout << x << endl;
	}
}



/***********************************************
 * Parsing method notes:
 *	
 *	Check functions:
 *	- Just checks current location to see if special character exists
 *
 *
 *	Special Helper Functions:
 *	- Only applies to a few weird situations:
 *		=> Quotation marks!
 *		=> Finding starts & ends of command & argument elements
 *
 *
 *
 *
 *
 * Issues:
 *
 *
 *
 ************************************************/

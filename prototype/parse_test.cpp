#include <iostream>
#include <iomanip>
#include <vector>
#include <cstring>
using namespace std;

// Check functions
char* checkSpace(char* phrase);
char* checkSemicolon(char* phrase);
char* checkAnd(char* phrase);
char* checkOr(char* phrase);
char* checkQuotes(char* phrase);

// Helper functions
int sizeQuote(char* phrase);
int sizeCmd(char* phrase);
char* newStrCpy(char* phrase, int size);
void printVector(vector<char*> v);
void deleteVectorCstrings(vector<char*> v);



void parseToVectors(char* phrase);


const int NUM_TESTS = 11;

int main()
{
	
	char* test[NUM_TESTS];

	test[0] = "ls -all\0";
	test[1] = "echo \"hello world\"";
	test[2] = "echo hello && goodbye";
	test[3] = "echo \"hello && goodbye\"";
	test[4] = "ls;";
	test[5] = "ls -a; echo hello && mkdir test || echo world; git status;";
	test[6] = "cd";
	test[7]	= "";
	test[8] = "ls    -a   ;";
	test[9] = ";&&echo \'hello\';";
	test[10] = ";||echo \'not home\'||echo \'is home\'";



	/* Some weird test results*/
	// test[11] = "echo hello ;";
	// Expects: 
	// echo hello ;
	
	// test[12] = ";;&&;";
	// Expects:
	// Syntax error
	

	// Needs handles on consecutive connectors (exception for semicolon)

	for(int i = 0; i < NUM_TESTS; ++i){
		cout << "Test " << i << " => " << test[i] << endl;
		parseToVectors(test[i]);
		cout << "====================================" << endl << endl;
	}



}


/*************************
 * CHECK FUNCTIONS
 *************************/

char* checkSpace(char* phrase)
{
	if(*phrase == ' ')
	{
		return phrase;
	}
	return NULL;
}

char* checkSemicolon(char* phrase)
{
	if(*phrase == ';')
	{
		return phrase;
	}
	return NULL;
}

char* checkAnd(char* phrase)
{
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
char* checkOr(char* phrase)
{
	if(phrase[0] == '|' && phrase[1] == '|')
	{
		return phrase;
	}	

	// Just one pipe throws an error
	else if(phrase[0] == '|'){
		cout << "Single Pipe Error!" << endl;
		exit(1);
	}
	return NULL;
}

// Returns current pointer if it's a quotation
char* checkQuotes(char* phrase)
{
	if(phrase[0] != '\"'){
		return NULL;
	}
	return phrase;
}

/*******************************
 *SPECIAL HELPER FUNCTIONS
 *******************************/

// Returns the end of the quotation or exits on error with no closing quote
int sizeQuote(char* phrase)
{
	for(int i = 1; phrase[i] != '\0'; ++i){
		if(phrase[i] == '\"')
		{
			return i + 1;
		}
	}
		
	//	error from unfinished quote
	throw "Unclosed string literal exception";
}

// Finds the size of the command
int sizeCmd(char* phrase)
{
	// cout << "Inside sizeCmd" << endl;
	int i = 0;
	while(phrase[i] != '\0')
	{
		if((checkQuotes(phrase + i) != NULL) ||
		   (checkSemicolon(phrase + i) != NULL) ||
		   (checkAnd(phrase + i) != NULL) ||
		   (checkOr(phrase + i) != NULL) ||
		   (checkSpace(phrase + i) != NULL))
		{
			return i;
		}
		++i;
	}
	return i;

}


// Dynamically allocates a new cstring to copy over data
char* newStrCpy(char* phrase, int size)
{
	char* new_copy = new char[size + 1];	// plus nullspace
	strncpy(new_copy, phrase, size);
	new_copy[size] = '\0';
	return new_copy;
}


// Prints a vector
void printVector(vector<char*> v)
{
	for(auto x: v){
		cout << x << endl;
	}
}

// Iterates through vector & deletes cstrings
void deleteVectorCstrings(vector<char*> v)
{
	for(auto x: v){
		delete []x;
	}
}


/*******************************
 * Test parsing function
 *******************************/


// Parses cstring into appropriate bucket vectors prototype
void parseToVectors(char* phrase)
{
	
	// Just to store commands & connectors
	vector<char*> commands, connectors;

	char* hold = NULL;	// Where cstring is copied to
	int length = 0;		// Used only for quote & cmd size
	int i = 0;		// Iterating value for the cstring


	while(phrase[i] != '\0'){

		// If a semicolon ;
		if(checkSemicolon(phrase + i) != NULL){
			length = 1;
			hold = newStrCpy(phrase + i, length);
			connectors.push_back(hold);
			i += length;
		}

		// If an AND ampersand &&
		else if(checkAnd(phrase + i) != NULL){
			length = 2;
			hold = newStrCpy(phrase + i, length);
			connectors.push_back(hold);
			i+=length;
		}

		// If an OR pipe ||
		else if(checkOr(phrase + i) != NULL){
			length = 2;
			hold = newStrCpy(phrase + i, length);
			connectors.push_back(hold);
			i += length ;
		}


		/* Needs separate implementation for matching single
		 * quotation marks */	
		
		// If has double quotation marks \"
		else if(checkQuotes(phrase + i) != NULL){
			int length = sizeQuote(phrase + i);
			hold = newStrCpy(phrase + i, length);
			commands.push_back(hold);
			i += length;
		}
		
		// If a space (commands & connectors ignore all whitespace)
		else if(checkSpace(phrase + i) != NULL){
			++i;
		}
	
		// If a command or argument
		else{
			int length = sizeCmd(phrase + i);
			hold = newStrCpy(phrase + i, length);
			commands.push_back(hold);
			i += length;
		}		
	}

	cout << endl << "Commands:" << endl << "-----" << endl;
	printVector(commands);

	cout << endl << "Connectors:" << endl << "-----" << endl;
	printVector(connectors);
}


/*********************************************************************
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
 *	Test Parsing function:
 *	- Parses the char string and breaks apart into 2 parts:
 *		=> commands
 *		=> connectors
 *
 *	- Handles plenty of edge cases and also exits on invalid inputs
 *		=> such as single ampersands or pipes
 *
 *
 *	Additional notes:
 *	- May require a class being built for parsing / filtering
 *	- Vector storage is not ideal when migrating over to tree format
 *	- Let's not deal with cstrings until the very end
 *
 **********************************************************************/




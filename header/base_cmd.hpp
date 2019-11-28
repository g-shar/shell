#ifndef __BASE_CMD_HPP__
#define __BASE_CMD_HPP__

#include <cstdlib>
#include <cstring>
#include <vector>
using namespace std;

class Base_Cmd {

public:
   	Base_Cmd(){};
   	virtual bool doWork()=0;

	/** Static Helper Functions **/
	
	static bool checkTest(char** argList, int size){
		int a = size - 1;
		int b = strlen(argList[a]) - 1;
		if(argList[0][0] == '[' && argList[a][b] == ']'){
			return true;
		}
		return false;
	}

	static char* checkPar(char* phrase)
	{
		if(*phrase == '(' || *phrase == ')')
		{
			return phrase;
		}
		return NULL;
	}

	static char* checkSpace(char* phrase)
	{
		if(*phrase == ' ')
		{
			return phrase;
		}
		return NULL;
	}

	static char* checkSemicolon(char* phrase)
	{
		if(*phrase == ';')
		{
			return phrase;
		}
		return NULL;
	}

	static char* checkAnd(char* phrase)
	{
		if(phrase[0] == '&' && phrase[1] == '&')
		{
			return phrase;
		}
		
		// Just one ampersand throws an error
		else if(phrase[0] == '&'){

			throw "checkAnd: Single Ampersand Error!\n \
				   Line 63 of base_cmd.hpp";
			exit(1);
		}

		return NULL;
	}

	// Returns current pointer if it's an or
	static char* checkOr(char* phrase)
	{
		if(phrase[0] == '|' && phrase[1] == '|')
		{
			return phrase;
		}	

		// Just one pipe throws an error
		else if(phrase[0] == '|'){
			throw "checkOr: Single Pipe Error!\n \
				   Line 78 of base_cmd.hpp";
			exit(1);
		}
		return NULL;
	}

	// Returns current pointer if it's a quotation
	static char* checkQuotes(char* phrase)
	{
		if(phrase[0] != '\"'){
			return NULL;
		}
		return phrase;
	}

	static char* checkComment(char* phrase)
	{
		if(phrase[0] == '#'){
			return phrase;
		}
		return NULL;
	}

	static char* checkCommand(char* phrase)
	{
		if(!(checkSemicolon(phrase) ||
			 checkOr(phrase) ||
			 checkAnd(phrase) ||
			 checkComment(phrase) ||
			 checkPar(phrase)))
		{
			return phrase;
		}
		return NULL;
	}

	static char* checkOperator(char* phrase){
		if(checkSemicolon(phrase) || checkOr(phrase) || checkAnd(phrase)){
			return phrase;
		}
		return NULL;
	}



	/*******************************
	 *SPECIAL HELPER FUNCTIONS
	 *******************************/

	// Returns the end of the quotation or exits on error with no closing quote
	static int sizeQuote(char* phrase)
	{
		for(int i = 1; phrase[i] != '\0'; ++i){
			if(phrase[i] == '\"')
			{
				return i + 1;
			}
		}
			
		//	error from unfinished quote
		throw "sizeQuote: Unfinished string literal exception\n \
			   Line 138 of base_cmd.hpp";
		exit(1);
	}

	// Finds the size of ONE argument
	static int sizeArg(char* phrase)
	{
		int i = 0;
		while(phrase[i] != '\0')
		{
			if((checkQuotes(phrase + i)) ||
			   (checkSemicolon(phrase + i)) ||
			   (checkAnd(phrase + i)) ||
			   (checkOr(phrase + i)) ||
			   (checkSpace(phrase + i)) ||
			   (checkPar(phrase + i)))
			{
				return i;
			}
			++i;
		}
		return i;

	}
	
	// Finds the size of an ENTIRE command
	static int sizeCmdObj(char* phrase)
	{
		int i = 0;
		while(phrase[i] != '\0')
		{
			if(!checkCommand(phrase + i))
			{
				return i;
			}
			++i;
		}
		return i;
	}

	// Finds the length from current pointer to end of string
	static int sizeEnd(char* phrase){
		int i = 0;
		while(phrase[i] != '\0')
		{
			++i;
		}
		return i;
	}

	// Dynamically allocates a new cstring to copy over data
	static char* newStrCpy(char* phrase, int size)
	{
		char* new_copy = new char[size + 1];	// plus nullspace
		strncpy(new_copy, phrase, size);
		new_copy[size] = '\0';
		return new_copy;
	}

	// Iterates through vector & deletes cstrings
	static void deleteVectorCstrings(vector<char*> v)
	{
		for(auto x: v){
			delete []x;
		}
	}


};

#endif

#ifndef __BASE_CMD_HPP__
#define __BASE_CMD_HPP__

#include <cstring>
#include <vector>
using namespace std;

class Base_Cmd {

public:
   	Base_Cmd(){};
   	virtual bool doWork()=0;

	/** Static Helper Functions **/
	
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
			cout << "Single Pipe Error!" << endl;
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
		throw "Unfinished string literal exception";
		exit(1);
	}

	// Finds the size of the command
	static int sizeArg(char* phrase)
	{
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

	static int sizeCmdObj(char* phrase)
	{
		int i = 0;
		while(phrase[i] != '\0')
		{
			if((checkSemicolon(phrase + i) != NULL) ||
			   (checkAnd(phrase + i) != NULL) ||
			   (checkOr(phrase + i) != NULL))
			{
				return i;
			}
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

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

	static en scan(string phrase){
		for(int i = 0; i < phrase.size(); ++i){
			if(phrase[i] == ">" && phrase[i + 1] == ">"){
				return en::APP;
			}

			if(phrase[i] == ">"){
				return en::OUT;
			}

			if(phrase[i] == "<"){
				return en::IN;
			}

			if(phrase[i] == "|"){
				return en::PIPE;
			}
		}
		return en::CMD;


	}

	static char* checkRedirect(char* phrase){
		if(checkIn(phrase) ||
		   checkOut(phrase) ||
		   checkApp(phrase) ||
		   checkPipe(phrase)){
		   return phrase;
		}
		return NULL;
	}

	static char* checkIn(char* phrase){
		if(*phrase == "<"){
			return phrase;
		}
		return NULL;
	}

	static char* checkOut(char* phrase){
		if(*phrase == ">"){
			return phrase;
		}
		return NULL;
	}

	static char* checkApp(char* phrase){
		if(phrase[0] == ">" && phrase[1] == ">")
		{
			return phrase;
		}


		else if(phrase[0] == ">")
		{
			throw "checkApp: Single Append Redirection Error!\n\
				   check base_cmd.hpp";			
			exit(1);
		}

		return NULL;
	}

	static char* checkPipe(char* phrase){
		if(*phrase == "|"){
			return phrase;
		}
		return NULL;
	}
	
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

	static Base* getRedirect(string phrase){
		phrase = trimWhitespace(phrase);
		int next = sizeRedirect(phrase);
		string right_file;
		string left_cmd;
		char* file = NULL;
		char* cmd = NULL;

		// if normal command object
		if(next == string::npos){
			return  new Cmd_Obj(phrase.c_str());
		}

		// Turns left & right sides into cstrings
		right_file = trimWhitespace(phrase.substr(next + 1));
		left_cmd = trimWhitespace(phrase.substr(0, next));

		if(right_file[0] == ">"){
			right_file = right_file.substr(1);
		}

		file = handleCstr(right_file.c_str());
		cmd = handleCstr(left_cmd.c_str());
			

		// Handles which object return
		else if(phrase[next] == "<"){
			return new Cmd_Obj(left, file, en::IN);
		}

		else if(phrase[next] == ">" && phrase[next] == ">"){
			return new Cmd_Obj(left, file, en::APP);
		}

		else if(phrase[next] == ">"){
			return new Cmd_Obj(left, file, en::OUT);
		}

		throw "Uncaught symbol? Base_cmd getRedirect();";
		exit(1);

	}
	
	static string trimWhitespace(string phrase){
		return trimTrail(trimLead(phrase));
	}

	static string trimLead(string phrase){
		string w = " \t";
		int start = phrase.find_first_not_of(w);
		return (start == string::npos) ? phrase : phrase.substr(start);
	}

	static string trimTrail(string phrase){
		string w = " \t";
		int end = phrase.find_last_not_of(w);
		return (end == string::npos) ? phrase : phrase.substr(0, end + 1);
	}


	static int sizeRedirect(string phrase){
		for(int i = 0; i < phrase.size(); ++i){
			//skip quotes
			if(phrase[i] == "\""){
				i += phrase.find("\"");
			}

			if(phrase[i] == "|" || phrase[i] == "<" || phrase[i] == ">"){
				return i;	
			}
		}	
		return phrase.size();
	}

	static int sizePipe(string phrase){
		for(int i = 0; i < phrase.size(); ++i){
			if(phrase[i] == "\""){
				i += phrase.find("\"");
			}

			if(phrase[i] == "|"){
				return i;
			}
		}
		return phrase.size();
	}


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

	static char* handleCstr(char* phrase){
		if(size == 0) return NULL;
		return newStrCpy(phrase, strlen(phrase));
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

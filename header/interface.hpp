#ifndef __INTERFACE_HPP__
#define __INTERFACE_HPP__


#include <vector>
#include "base_cmd.hpp"

class Interface: public Base_Cmd{
private:
	Base_Cmd* call;

	void parse(char* input){
		vector<char*> base_commands;	//	 
		char* hold = NULL;				//  For copying cstrings
		int length = 0;					//	To help determine quote / string size
		int i = 0;						//	Iterating value for input

		
		while(input[i] != '\0')
		{
			// Semicolons
			if(Base_Cmd::checkSemicolon(input + i) != NULL)
			{
				length = 1;
				hold = Base_Cmd::newStrCpy(input + i, length);
				base_commands.push_back(hold);
				i += length;
			}

			else if(Base_Cmd::checkAnd(input + i) != NULL)
			{
				length = 2;
				hold = Base_Cmd::newStrCpy(input + i, length);
				base_commands.push_back(hold);
				i += length;			
			}
			
			else if(Base_Cmd::checkOr(input + i) != NULL)
			{
				length = 2;
				hold = Base_Cmd::newStrCpy(input + i, length);
				base_commands.push_back(hold);
				i += length;
			}
		}

	}

public:
	Interface(char* Cmd):{
		
	}

	virtual bool doWork(){
		return call->doWork();
	}





}

#ifndef __INTERFACE_HPP__
#define __INTERFACE_HPP__


#include <queue>
#include <vector>
#include "base_cmd.hpp"
#include "cmd_obj.hpp"

class Interface: public Base_Cmd{
private:
	Base_Cmd* call;

	void parse(char* input){
		vector<char*> base_commands;	//	Vector of commands
		char* hold = NULL;				//  For copying cstrings
		int length = 0;					//	To help determine quote / string size
		int i = 0;						//	Iterating value for input

		
		/** Puts all connectors & command objects in vector **/
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

			// Ands
			else if(Base_Cmd::checkAnd(input + i) != NULL)
			{
				length = 2;
				hold = Base_Cmd::newStrCpy(input + i, length);
				base_commands.push_back(hold);
				i += length;			
			}
			
			// Ors
			else if(Base_Cmd::checkOr(input + i) != NULL)
			{
				length = 2;
				hold = Base_Cmd::newStrCpy(input + i, length);
				base_commands.push_back(hold);
				i += length;
			}

			// Space
			else if(Base_Cmd::checkSpace(input + i) != NULL){
				++i;
			}

			// Any cmd_obj
			else{
				int length = sizeCmdObj(phrase + i);	
				hold = newStrCpy(phrase + i, length);
				base_commands.push_back(hold);
				i += length;
			}
		}

		void buildTree(vector<char*> base_commands)
		{
			Base_Cmd* cur = NULL; 
			queue<Cmd_Obj*> Q;
			int i = 0;

			while(i < base_commands.size()){
				if(checkSemicolon(base_commands[i]))
				{
					base_commands[
				}

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

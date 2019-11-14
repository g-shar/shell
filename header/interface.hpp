#ifndef __INTERFACE_HPP__
#define __INTERFACE_HPP__


#include <queue>
#include <vector>
#include <iostream>
#include <cstring>
using namespace std;

#include "base_cmd.hpp"
#include "cmd_obj.hpp"
#include "connectors.hpp"
#include "and.hpp"
#include "or.hpp"
#include "semicolon.hpp"

class Interface: public Base_Cmd{
private:
	Base_Cmd* call;


	// Tree construction with a vector (skewed)
	void buildTree(vector<char*> base_commands)
	{
		Connectors* cur = NULL; 
		Base_Cmd* temp = NULL;
		queue<Cmd_Obj*> Q;
		int i = 0;

		while(i < base_commands.size())
		{

			if(base_commands[i] != ";" || base_commands[i] != "||" || base_commands[i] != "&&")
			{
				Q.push(new Cmd_Obj(base_commands[i]));
				++i;
				continue;
			}

			else if(checkSemicolon(base_commands[i]))
			{
				temp = new Semicolon();
			}
			else if(checkOr(base_commands[i]))
			{
				temp = new Or();
			}
			else{
				temp = new And();
			}

			// Initializing root
			if(call == NULL){
				call = temp;	
				cur = call;
			}

			// Advance tree
			else{
				cur->setRight(temp);
				cur->setLeft(Q.front());
				Q.pop();
				cur = cur->right;		// fix this ugly mess later
			}
			++i;
		}

		// Closing tree
		cur->setLeft(Q.front());
		cur->setRight(Q.back());
	}

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
				int length = sizeCmdObj(input + i);	
				hold = newStrCpy(input + i, length);
				base_commands.push_back(hold);
				i += length;
			}

			// Constructs the tree
			buildTree(base_commands);

			/* TEST */
			printV(base_commands);
		}
	}

public:
	Interface(char* cmd){
		parse(cmd);	
	}

	virtual bool doWork(){
		return call->doWork();
	}

	/* Test functions */
	void printV(vector<char*> temp){
		for(auto x: temp){
			cout << x;
		}
	}

};
#endif

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

	// Helper function (returns the correct connector)
	Base_Cmd* getConnector(char* sign, Base_Cmd* left, Base_Cmd* right){
		if(checkSemicolon(sign)){
			return new Semicolon(left, right);
		}
		else if(checkAnd(sign)){
			return new And(left, right);
		}
		else if(checkOr(sign)){
			return new Or(left, right);
		}
		throw "no connector exception";
	}
		


	// Tree construction with a vector (skewed)
	void buildTree(vector<char*> base_commands)
	{

		queue<Base_Cmd*> Q;
		char* temp = NULL;
		int i = base_commands.size() - 1;

		// Currently not handling "echo hello;"
		if(base_commands[i] == ";"){
		
		}

		while(i >= 0)
		{
			// construct tree bottom up
			if(Q.size() == 2){
				Q.push(getConnector(temp, Q.back(), Q.front()));
				Q.pop();
				Q.pop();
				temp = NULL;
			}

			if(!(checkSemicolon(base_commands[i]) || checkOr(base_commands[i]) || checkAnd(base_commands[i])))
			{
				Q.push(new Cmd_Obj(base_commands[i]));
				--i;
				continue;
			}

			else if(temp == NULL){
				temp = base_commands[i];
			}

			else{
				throw "two consecutive connectors exception";
			}


			--i;
		}
		
		/*
		if(temp != NULL){
			throw "incomplete connector exception";
			// e.g. "echo hello ||" will crash
			// as of right now "echo hello;" will also crash even though it is valid
		}
		*/

		call = Q.front();
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

		}
	
		// Constructs the tree
		buildTree(base_commands);

		/* TEST */
		// printV(base_commands);
	}

public:
	
	Interface(char* cmd){
		parse(cmd);	
	}

	Interface(){}

	void setCommand(char* cmd){
		parse(cmd);
	}

	virtual bool doWork(){
		return call->doWork();
	}

	/* Test functions */
	void printV(vector<char*> temp){
		for(auto x: temp){
			cout << x << endl;
		}
	}

};
#endif

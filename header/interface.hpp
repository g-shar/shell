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
			// cout << "Semicolon" << endl;
			return new Semicolon(left, right);
		}
		else if(checkAnd(sign)){
			// cout << "And" << endl;
			return new And(left, right);
		}
		else if(checkOr(sign)){
			// cout << "Or" << endl;
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

		// just a single connector error
		if(!checkCommand(base_commands[i]) && i == 0){
			throw "just a connector exception";	
		}

		// handles ending semicolon case
		else if(checkSemicolon(base_commands[i]) && checkCommand(base_commands[i-1])){
			Q.push(getConnector(base_commands[i], new Cmd_Obj(base_commands[i-1]), NULL));
			i-=2;
		}

		while(i >= 0)
		{	
			// If command, push to queue
			if(checkCommand(base_commands[i]))
			{
				Q.push(new Cmd_Obj(base_commands[i]));
			}

			// if connector, store temporarily
			else if(temp == NULL){
				temp = base_commands[i];
			}

			// if double connectors, throw exception
			else{
				throw "two consecutive connectors exception";
			}

			// Once there are 2 items in queue, connect & create tree
			if(Q.size() == 2){
				Q.push(getConnector(temp, Q.back(), Q.front()));
				Q.pop();
				Q.pop();
				temp = NULL;
			}

			--i;
		}
		
		// sets the root node to the front of the queue
		call = Q.front();
	}

	// if receiving input from cmd prompt
	void parse(int argv, char** argc){
		vector<char*> base_commands;	
		int i;

		for(i = 0; argc[i] != NULL; ++i){
			base_commands.push_back(argc[i]);
		}	

		// for safety premeasures but it seems like main args includes NULL
		base_commands.push_back(NULL);
		printV(base_commands);
		// buildTree(base_commands);
	}

	// if receiving general input
	void parse(char* input){
		vector<char*> base_commands;	//	Vector of commands
		char* hold = NULL;				//  For copying cstrings
		int length = 0;					//	To help determine quote / string size
		int i = 0;						//	Iterating value for input

		
		/** Puts all connectors & command objects in vector **/
		while(input[i] != '\0')
		{
			cout << "Iteration => " << i << endl;

			// Semicolons
			if(checkSemicolon(input + i) != NULL)
			{
				length = 1;
				hold = newStrCpy(input + i, length);
				base_commands.push_back(hold);
				i += length;
			}

			// Ands
			else if(checkAnd(input + i) != NULL)
			{
				length = 2;
				hold = newStrCpy(input + i, length);
				base_commands.push_back(hold);
				i += length;			
			}
			
			// Ors
			else if(checkOr(input + i) != NULL)
			{
				length = 2;
				hold = newStrCpy(input + i, length);
				base_commands.push_back(hold);
				i += length;
			}

			// Space
			else if(checkSpace(input + i) != NULL){
				++i;
			}

			// Comment
			else if(checkComment(input + i) != NULL){
				i = -1;
			}

			// Any cmd_obj
			else{
				length = sizeCmdObj(input + i);	
				hold = newStrCpy(input + i, length);
				base_commands.push_back(hold);
				i += length;
			}

		}

		base_commands.push_back(NULL);
		printV(base_commands);
		// Constructs the tree
		// buildTree(base_commands);

		/* TEST */
		// printV(base_commands);
	}

public:
	
	Interface(char* cmd){
		parse(cmd);	
	}

	Interface(){}

	Interface(int argv, char** argc){
		parse(argv, argc);
	}

	void setCommand(char* cmd){
		parse(cmd);
	}

	void setCommand(int argv, char** argc){
		parse(argv, argc);
	}

	virtual bool doWork(){
		return call->doWork();
	}

	/* Test functions */
	void printV(vector<char*> temp){
		cout << "This vector contains: " << endl;
		for(auto x: temp){
			cout << x << endl;
		}
	}

};
#endif

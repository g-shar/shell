#ifndef __INTERFACE_HPP__
#define __INTERFACE_HPP__


#include <stack>
#include <vector>
#include <iostream>
#include <cstring>
#include <string>
#include <queue>
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
		throw "getConnector: Nonexistent connector!\n \
			   Line 37 from interface.hpp";
		exit(1);
	}



	vector<char*> buildPostFix(vector<char*> base_commands){
		vector<char*> postFixVector;
		stack<char*> hold;
		int pars = 0;

		for(int i = 0; i < base_commands.size(); ++i){

			// If open parens
			if(*base_commands[i] == '('){
				++pars;				
				hold.push(base_commands[i]);
			}

			// If closed parens
			else if(*base_commands[i] == ')'){
				while(*hold.top() != '('){
					postFixVector.push_back(hold.top());
					hold.pop();
				}
				hold.pop();	// get rid of that last parens
				--pars;
			}

			// If Operand
			else if(checkCommand(base_commands[i])){
				postFixVector.push_back(base_commands[i]);	
			}

			// If operator, push to stack and replace previous if no other operator / no cur parens
			else{
				if(!hold.empty() && !pars){
					postFixVector.push_back(hold.top());
					hold.pop();
				}
				hold.push(base_commands[i]);
			}
		}

		// Empty remains of the stack
		while(!hold.empty()){
			postFixVector.push_back(hold.top());
			hold.pop();
		}

		return postFixVector;
	}

	
	void buildTree2(vector<char*> base_commands)
	{

		stack<Base_Cmd*> tree;
		Base_Cmd* leftLeaf;
		Base_Cmd* rightLeaf;
		Base_Cmd* center;
		
		
		for(int i = 0; i < base_commands.size(); ++i){

			// Push new command object onto stack
			if(checkCommand(base_commands[i])){
				tree.push(getCmdObj(base_commands[i]));	
			}

			// Destack base commands from stack and attach to operator before pushing onto stack again
			else if(checkOperator(base_commands[i])){
				rightLeaf = tree.top();
				tree.pop();
				leftLeaf = tree.top();
				tree.pop();
				center = getConnector(base_commands[i], leftLeaf, rightLeaf);
				tree.push(center);
			}
		}

		call = tree.top();
	}


	// if receiving input from cmd prompt
	void parse(int argv, char** argc){
		char* input = NULL;		// cstring holder
		int i;					// iterator
	    int	sum = argv - 2;		// in order to make room for spaces

		// Get size of arguments
		for(i = 1; argc[i]; ++i){
			sum += strlen(argc[i]);		
		}

		input = new char[sum];

		// Stack all arguments into 1 cstring
		for(i = 1; argc[i]; ++i){
			strcat(input, argc[i]);

			// Keep adding spaces if there's another element
			if(argc[i + 1]){
				strcat(input, " ");
			}
		}

		// Calls an already implemented parse
		this->parse(input);
	}

	// if receiving general input
	void parse(char* input){
		vector<char*> base_commands;	//	Vector of commands
		char* hold = NULL;				//  For copying cstrings
		int length = 0;					//	To help determine quote / string size
		int i = 0;						//	Iterating value for input
		int closer = 0;					// 	Keeps track of closed parentheses

		
		/** Puts all connectors & command objects in vector **/
		while(input[i] != '\0')
		{
			// Parentheses
			if(checkPar(input + i) != NULL)
			{
				// If open parentheses
				if(input[i] == '('){
					++closer;
				}				

				// If closed without an open parentheses
				else if(closer == 0){
					throw "parse: Unclosed parentheses error!\n \
						   Line 171 from interface.hpp";
					exit(1);
				}

				// If closed parentheses
				else{
					--closer;
				}

				length = 1;
				hold = newStrCpy(input + i, length);
				base_commands.push_back(hold);
				i += length;
			}

			// Semicolons
			else if(checkSemicolon(input + i) != NULL)
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
				break;
			}

			// Any cmd_obj
			else{
				length = sizeCmdObj(input + i);	
				hold = newStrCpy(input + i, length);
				base_commands.push_back(hold);
				i += length;
			}

		}

		// check for unclosed parentheses
		if(closer != 0){
			throw "parse: Unclosed Parentheses!\n \
				   Line 235 from interface.hpp";
			exit(1);
		}

		// reorder the vector to postfix
		vector<char*> postFix = buildPostFix(base_commands);

	
		// build the tree!
		buildTree2(postFix);


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

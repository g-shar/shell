#ifndef __SEMICOLON_HPP__
#define __SEMICOLON_HPP__

#include "connectors.hpp"

class Semicolon: public Connectors {
public:
	Semicolon():Connectors(NULL, NULL){}
	Semicolon(Base_Cmd* left):Connectors(left, NULL){}
	Semicolon(Base_Cmd* left, Base_Cmd* right):Connectors(left,right){}
   	virtual bool doWork() {
   	   	left->doWork();
		if(right){
   	   		return right->doWork();
		}
		return true;
   	}
};

#endif

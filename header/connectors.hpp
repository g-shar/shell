#ifndef __CONNECTORS_HPP__
#define __CONNECTORS_HPP__

#include "base_cmd.hpp"

class Connectors: public Base_Cmd {
public:
   	Base_Cmd* left; 
   	Base_Cmd* right;

protected:
   	Connectors(Base_Cmd* left, Base_Cmd* right){
   	   this->left=left;
   	   this->right=right;
   	}

public:
   	virtual bool doWork()=0;
   	void setLeft(Base_Cmd* l)
   	{
		left = l;
   	}
   	void setRight(Base_Cmd* r)
   	{
		right = r;
	}
	Base_Cmd* getLeft(){
		return left;
	}
	Base_Cmd* getRight(){
		return right;
	}

};

#endif

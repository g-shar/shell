#ifndef __OR_HPP__
#define __OR_HPP__

#include "connectors.hpp"

class Or: public Connectors {
public:

	Or(): Connectors(NULL, NULL){}
	Or(Base_Cmd* left, Base_Cmd* right): Connectors(left, right){}
   	virtual bool doWork(){
   	   if(left->doWork()==false)
   	   {
		   return right->doWork();
   	   }
   	   return true;
   	}
};

#endif

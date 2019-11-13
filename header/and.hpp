#ifndef __AND_HPP__
#define __AND_HPP__

#include <iostream>
#include "connectors.hpp"

using namespace std;

class And: public Connectors {
public:
   And(Base_Cmd* left, Base_Cmd* right): Connectors(left, right){}
   virtual bool doWork(){
      if(left->doWork()==true)
      {
         return right->doWork();
      }
      return false;
   }
};

#endif

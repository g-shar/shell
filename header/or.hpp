#ifndef __OR_HPP__
#define __OR_HPP__

#include "connectors.hpp"

class Or: public Connectors {
public:
   Or(Base_Cmd* left, Base_Cmd* right): Connectors(left, right){}
   virtual bool doWork(){
      if(left->doWork()==false)
      {
         return right->doWork();
      }
      return false;
   }
};

#endif

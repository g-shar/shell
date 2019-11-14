#ifndef __CONNECTORS_HPP__
#define __CONNECTORS_HPP__

#include "base_cmd.hpp"

class Connectors: public Base_Cmd {
protected:
   Base_Cmd* left; 
   Base_Cmd* right;
   Connectors(Base_Cmd* left, Base_Cmd* right){
      this->left=left;
      this->right=right;
   }

public:
   virtual bool doWork()=0;

};

#endif

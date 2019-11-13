#ifndef __FULL_CMD_HPP__
#define __FULL_CMD_HPP__

#include "cmd_obj.hpp"
#include "connectors.hpp"

class Full_Cmd {
public:
   Full_Cmd(string command){};
   void execute(){
      root->doWork();
   }

private:
   Base_Cmd* root
   void parse();
};

#endif

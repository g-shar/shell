#ifndef __CMD_OBJ_HPP__
#define __CMD_OBJ_HPP__

#include "base_cmd.hpp"

class Cmd_Obj: public Base_Cmd {
private:
   bool doWork();
   void parse();
   char* executable;
   char* argList[];
};

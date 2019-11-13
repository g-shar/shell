#ifndef __CMD_OBJ_HPP__
#define __CMD_OBJ_HPP__

#include "base_cmd.hpp"

class Cmd_Obj: public Base_Cmd {
public:
   Cmd_Obj(char* cmd, char* list[]): executable(cmd), argList(list){};
   virtual bool doWork();

private:
   void parse();
   char* executable;
   char** argList;
};

#endif

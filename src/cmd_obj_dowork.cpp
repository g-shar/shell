#ifndef __CMD_OBJ_DOWORK_CPP__
#define __CMD_OBJ_DOWORK_CPP__

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string>
#include<iostream>

#include "../header/cmd_obj.hpp"

using namespace std;

bool Cmd_Obj::doWork() {
   bool process=true;
   int status;
   pid_t pid;

   pid=fork();

   if(pid==0)
   { 
      execvp(this->executable, this->argList);      
      perror("execvp");
      exit(1);
   }
   else if(pid==-1)
   {
      perror("fork");
      exit(1);
   }
   else
   {
      waitpid(-1, &status, 0);
   }
   if(WIFEXITED(status))
   {
      if(WEXITSTATUS(status)==0)
      {
         return true;
      }
      else
      {
         return false;
      }
   }
   return false;
}

#endif

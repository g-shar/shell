#ifndef __CMD_OBJ_DOWORK_CPP__
#define __CMD_OBJ_DOWORK_CPP__

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string>

#include "cmd_obj.hpp"

bool doWork() {
   int status;
   pid_t pid;

   pid=fork();

   if(pid==0)
   {
      if(execvp(this->executable, this->argList)<0)
      {
         perror("execvp");
      }
      exit(0);
   }
   else if(pid==-1)
   {
      perror("fork");
      exit(1);
   }
   else if(pid>0)
   {
      waitpid(-1, &status, 0);
   }

   return 0;
}

#endif

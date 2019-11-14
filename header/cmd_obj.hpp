#ifndef __CMD_OBJ_HPP__
#define __CMD_OBJ_HPP__

#include "base_cmd.hpp"

class Cmd_Obj: public Base_Cmd {
public:
	Cmd_Obj(char* cmd){
		parse(cmd);		
	}

	Cmd_Obj(char* cmd, char* list[]): executable(cmd), argList(list){};

	~Cmd_Obj(){
		for(int i = 0; i < size; ++i)
		{
			delete[] argList[i];
		}
	}

	virtual bool doWork();

private:

	void parse(char* cmd){
		int i = 0;			// Counter for the command passed in
		int j = 0;			// Counter for the cstr arr
		int length = 0;		// For length determination

		while(cmd[i] != '\0')
		{
			if(checkQuotes(cmd) != NULL)
			{
				length = sizeQuote(cmd + i);	
			}			

			else if(checkSpace(cmd) != NULL)
			{
				++i;
				continue;
			}

			else{
				length = sizeArg(cmd + i);
			}

			argList[j] = newStrCpy(cmd + i, length);
			i += length;
			++j;
		}
		cmd = argList[0];
		size = j;
  	}

   	char* executable;
   	char** argList;
	int size;
};

#endif

#ifndef __BASE_CMD_HPP__
#define __BASE_CMD_HPP__

class Base_Cmd {
public:
   Base_Cmd(){};
   virtual bool doWork()=0;
};

#endif

#ifndef __IO_CMD_TEST_HPP__
#define __IO_CMD_TEST_HPP__

#include <cstring>
#include <fstream>
#include "../header/cmd_obj.hpp"
#include "../header/interface.hpp"

TEST(IOCmdTestSet, OutputOperationTest) {
   string cmd="echo hello > input.txt";
   char fullCmd[cmd.size()+1];
   strcpy(fullCmd, cmd.c_str());
   Interface* object1= new Interface(fullCmd);
   EXPECT_EQ(object1->doWork(), true);

}

TEST(IOCmdTestSet, OutputAppendTest) {
   char* argList="echo appended >> input.txt";
   Interface* object1= new Interface(argList);
  
   bool result=object1->doWork();
 
   EXPECT_EQ(result, true);

}

TEST(IOCmdTestSet, InputTest) {
   char* argList="cat < input.txt";
   Interface* object1= new Interface(argList);

   EXPECT_EQ(object1->doWork(), true);
}

TEST(IOCmdTestSet, ErrorTest) {
   char* argList="eho error > input.txt";

   Interface* object1= new Interface(argList);

   EXPECT_EQ(object1->doWork(), true);
}


#endif

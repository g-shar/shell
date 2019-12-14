#ifndef __PIPE_CMD_TEST_HPP__
#define __PIPE_CMD_TEST_HPP__

#include <fstream>
#include "../header/cmd_obj.hpp"

TEST(IOCmdTestSet, onePipeTest) {
   char* fullCmd="echo hello | tr a-z A-Z";
   Interface* object1= new Interface(fullCmd);
   EXPECT_EQ(object1->doWork(), true);

}

TEST(IOCmdTestSet, twoPipeTest) {
   char* argList="echo APPENDED | tr A-Z a-z | tr a-z A-Z";
   Interface* object1= new Interface(fullCmd);
   
   bool result=object1->doWork();
   EXPECT_EQ(result, true);

}

TEST(IOCmdTestSet, threePipeTest) {
   char* argList="echo thirdTry | tr a-z A-Z | tr A-Z a-z | tr a-z A-Z";
   Interface* object1= new Interface(argList);

   EXPECT_EQ(object1->doWork(), true);
}

TEST(IOCmdTestSet, ErrorTest) {
   char* argList="eho error | tr a-z";

   Interface* object1= new Interface(argList);

   EXPECT_EQ(object1->doWork(), false);
}


#endif

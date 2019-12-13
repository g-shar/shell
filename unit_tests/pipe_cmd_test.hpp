#ifndef __TEST_CMD_TEST_HPP__
#define __TEST_CMD_TEST_HPP__

#include <fstream>
#include "../header/cmd_obj.hpp"

TEST(IOCmdTestSet, OutputOperationTest) {
   char* fullCmd="echo hello < input.txt";
   Interface* object1= new Interface(fullCmd);
   EXPECT_EQ(object1->doWork(), true);

}

TEST(IOCmdTestSet, OutputAppendTest) {
   char* argList="echo appended >> input.txt";
   Interface* object1= new Interface(fullCmd);
   
   bool result=object1->doWork();
   ifstream inFS;
   inFS.open("input.txt");
   string x="":
   inFS>>x;

   EXPECT_EQ(result, true);
   EXPECT_EQ(x, "appended");

}

TEST(IOCmdTestSet, InputTest) {
   char* argList="cat < input.txt";
   Interface* object1= new Interface(argList);

   EXPECT_EQ(object1->doWork(), true);
}

TEST(IOCmdTestSet, ErrorTest) {
   char* argList="eho error > input.txt";

   Interface* object1= new Interface(argList);

   EXPECT_EQ(object1->doWork(), false);
}


#endif

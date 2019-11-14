#ifndef __CO_DOWORK_TEST_HPP__
#define __CO_DOWORK_TEST_HPP__

#include "gtest/gtest.h"
#include "../header/cmd_obj.hpp"

TEST(Cmd_ObjTestSet, EchoTest) {
   char* argList[5];
   const char* cmd="echo";

   argList[0]="echo";
   argList[1]="hello";
   argList[2]="&&";
   argList[3]="goodbye";
   argList[4]=NULL;

   Base_Cmd* object= new Cmd_Obj(cmd, argList);

   EXPECT_EQ(object->doWork(), true);   //should return true since command is valid
}

TEST(Cmd_ObjTestSet, lsTest) {
   char* argList[2];
   const char* cmd="ls";

   argList[0]="ls";
   argList[1]=NULL;

   Base_Cmd* object= new Cmd_Obj(cmd, argList);

   EXPECT_EQ(object->doWork(), true);  //should return true since command is valid
}

TEST(Cmd_ObjTestSet, gitBranchTest) {
   char* argList[3];
   const char* cmd="git";

   argList[0]="git";
   argList[1]="branch";
   argList[2]=NULL;

   Base_Cmd* object= new Cmd_Obj(cmd, argList);

   EXPECT_EQ(object->doWork(), true);  //should return true since command is valid
}

TEST(Cmd_ObjTestSet, ExecuteFailTest) {
   char* argList[5];
   const char* cmd="eho";

   argList[0]="eho";
   argList[1]="hello";
   argList[2]="&&";
   argList[3]="goodbye";
   argList[4]=NULL;

   Base_Cmd* object= new Cmd_Obj(cmd, argList);

   EXPECT_EQ(object->doWork(), false);  //should return false since command is invalid
}

#endif

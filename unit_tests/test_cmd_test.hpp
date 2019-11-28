#ifndef __TEST_CMD_TEST_HPP__
#define __TEST_CMD_TEST_HPP__

#include "../header/cmd_obj.hpp"

TEST(TestCmdTestSet, NoFlagTest) {
   char* argList[3];
   char* cmd="test";
   
   argList[0]="test";
   argList[1]="src";
   argList[2]=NULL;
  
   char* cmd2="test"; 
   char* argList2[3];
   
   argList2[0]="test";
   argList2[1]="sr";
   argList2[2]=NULL;
   
   Base_Cmd* object1= new Cmd_Obj(argList[0], argList);
   Base_Cmd* object2= new Cmd_Obj(cmd2, argList2); 
   
   cout<<argList[0]<<endl;
   cout<<argList[1]<<endl;
   //object1->printCommands();
   //object2->printCommands();

   EXPECT_EQ(object1->doWork(), true);
   EXPECT_EQ(object2->doWork(), false);

}

TEST(TestCmdTestSet,dFlagTest) {
   char* argList[4];
   char* cmd="test";
   
   argList[0]="test";
   argList[1]="-d";
   argList[2]="src";
   argList[3]=NULL;

   Base_Cmd* object= new Cmd_Obj(cmd, argList);
   
   EXPECT_EQ(object->doWork(), true);   //should return true since command is valid

   char* argList2[4];
   char* cmd2="test";
   
   argList2[0]="test";
   argList2[1]="-d";
   argList2[2]="names.txt";
   argList2[3]=NULL;

   Base_Cmd* object2= new Cmd_Obj(cmd2, argList2);
   
   EXPECT_EQ(object2->doWork(), false);   //should return true since command is valid
}

TEST(TestCmdTestSet,fFlagTest) {
   char* argList[4];
   char* cmd="test";
   
   argList[0]="test";
   argList[1]="-f";
   argList[2]="src";
   argList[3]=NULL;

   Base_Cmd* object= new Cmd_Obj(cmd, argList);
   
   EXPECT_EQ(object->doWork(), false);   //should return true since command is valid

   char* argList2[4];
   
   argList2[0]="test";
   argList2[1]="-f";
   argList2[2]="names.txt";
   argList2[3]=NULL;

   Base_Cmd* object2= new Cmd_Obj(cmd, argList2);
   
   EXPECT_EQ(object2->doWork(), true);

   char* argList3[4];
   
   argList3[0]="test";
   argList3[1]="-f";
   argList3[2]="name.txt";
   argList3[3]=NULL;

   Base_Cmd* object3= new Cmd_Obj(cmd, argList3);
   
   EXPECT_EQ(object3->doWork(), false);
}

TEST(TestCmdTestSet,eFlagTest) {
   char* argList[4];
   char* cmd="test";
   
   argList[0]="test";
   argList[1]="-e";
   argList[2]="unit_tests";
   argList[3]=NULL;

   Base_Cmd* object= new Cmd_Obj(cmd, argList);
   
   EXPECT_EQ(object->doWork(), true);   //should return true since command is valid


   char* argList2[4];
   
   argList2[0]="test";
   argList2[1]="-e";
   argList2[2]="names.txt";
   argList2[3]=NULL;

   Base_Cmd* object2= new Cmd_Obj(cmd, argList2);
   
   EXPECT_EQ(object2->doWork(), true);


   char* argList3[4];
   
   argList3[0]="test";
   argList3[1]="-e";
   argList3[2]="unit_test";
   argList3[3]=NULL;

   Base_Cmd* object3= new Cmd_Obj(cmd, argList3);
   
   EXPECT_EQ(object3->doWork(), false);
}

TEST(TestCmdTestSet, SymbolTest) {
   char* argList[5];
   char* cmd="[";
   
   argList[0]="[";
   argList[1]="-e";
   argList[2]="unit_tests";
   argList[3]="]";
   argList[4]=NULL;

   Base_Cmd* object= new Cmd_Obj(cmd, argList);
   
   EXPECT_EQ(object->doWork(), true);   //should return true since command is valid


   char* argList2[5];
   
   argList2[0]="[";
   argList2[1]="-d";
   argList2[2]="names.txt";
   argList2[3]="]";
   argList2[4]=NULL;

   Base_Cmd* object2= new Cmd_Obj(cmd, argList2);
   
   EXPECT_EQ(object2->doWork(), false);


   char* argList3[5];
   
   argList3[0]="[";
   argList3[1]="-f";
   argList3[2]="names.txt";
   argList3[3]="]";
   argList3[4]=NULL;

   Base_Cmd* object3= new Cmd_Obj(cmd, argList3);
   
   EXPECT_EQ(object3->doWork(), true);
}

#endif

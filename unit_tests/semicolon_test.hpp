#ifndef __SEMICOLON_TEST_HPP__
#define __SEMICOLON_TEST_HPP__

#include "../header/semicolon.hpp"

TEST(SemicolonTestSet, twoCommandSuccessTest) {
   char* argList[5];
   char* cmd="echo";
   
   argList[0]="echo";
   argList[1]="hello";
   argList[2]="&&";
   argList[3]="goodbye";
   argList[4]=NULL;
  
   char* cmd2="ls"; 
   char* argList2[2];
   
   argList2[0]="ls";
   argList2[1]=NULL;


   Base_Cmd* object1= new Cmd_Obj(argList[0], argList);
   Base_Cmd* object2= new Cmd_Obj(argList2[0], argList2);

   Base_Cmd* andConnect= new Semicolon(object1, object2);  
   
   EXPECT_EQ(andConnect->doWork(), true);    //returns true since both commands are succesful

}

TEST(SemicolonTestSet, FirstCommandFailsTest) {
   char* argList[5];
   char* cmd="eho";
   
   argList[0]="eho";
   argList[1]="hello";
   argList[2]="&&";
   argList[3]="goodbye";
   argList[4]=NULL;
  
   char* cmd2="ls"; 
   char* argList2[2];
   
   argList2[0]="ls";
   argList2[1]=NULL;


   Base_Cmd* object1= new Cmd_Obj(argList[0], argList);
   Base_Cmd* object2= new Cmd_Obj(argList2[0], argList2);

   Base_Cmd* andConnect= new Semicolon(object1, object2);  
   
   EXPECT_EQ(andConnect->doWork(), true);  //returns true since 2nd command is executed

}
TEST(SemicolonTestSet, SecondCommandFailsTest) {
   char* argList[5];
   char* cmd="echo";
   
   argList[0]="echo";
   argList[1]="hello";
   argList[2]="&&";
   argList[3]="goodbye";
   argList[4]=NULL;
  
   char* cmd2="ls"; 
   char* argList2[2];
   
   argList2[0]="s";
   argList2[1]=NULL;


   Base_Cmd* object1= new Cmd_Obj(argList[0], argList);
   Base_Cmd* object2= new Cmd_Obj(argList2[0], argList2);

   Base_Cmd* andConnect= new Semicolon(object1, object2);  
   
   EXPECT_EQ(andConnect->doWork(), false);  //returns false since 2nd command fails
}

#endif

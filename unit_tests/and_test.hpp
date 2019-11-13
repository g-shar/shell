#ifndef __AND_TEST_HPP__
#define __AND_TEST_HPP__

#include "../header/and.hpp"

TEST(AndTestSet, twoCommandSuccessTest) {
   char* argList[5];
   char* cmd="echo";
   
   argList[0]="echo";
   argList[1]="first";
   argList[2]="command";
   argList[3]="executed";
   argList[4]=NULL;
  
   char* cmd2="ls"; 
   char* argList2[2];
   
   argList2[0]="ls";
   argList2[1]=NULL;


   Base_Cmd* object1= new Cmd_Obj(argList[0], argList);
   Base_Cmd* object2= new Cmd_Obj(argList2[0], argList2);

   Base_Cmd* andConnect= new And(object1, object2);  
   
   EXPECT_EQ(andConnect->doWork(), true);    //since both commands are succesful

}

TEST(AndTestSet, FirstCommandFailsTest) {
   char* argList[5];
   char* cmd="eho";
   
   argList[0]="eho";
   argList[1]="first";
   argList[2]="command";
   argList[3]="executed";
   argList[4]=NULL;
  
   char* cmd2="ls"; 
   char* argList2[2];
   
   argList2[0]="ls";
   argList2[1]=NULL;


   Base_Cmd* object1= new Cmd_Obj(argList[0], argList);
   Base_Cmd* object2= new Cmd_Obj(argList2[0], argList2);

   Base_Cmd* andConnect= new And(object1, object2);  
   
   EXPECT_EQ(andConnect->doWork(), false);  //returns false since no commands are executed

}
TEST(AndTestSet, SecondCommandFailsTest) {
   char* argList[5];
   char* cmd="echo";
   
   argList[0]="echo";
   argList[1]="first";
   argList[2]="command";
   argList[3]="executed";
   argList[4]=NULL;
  
   char* cmd2="ls"; 
   char* argList2[2];
   
   argList2[0]="s";
   argList2[1]=NULL;


   Base_Cmd* object1= new Cmd_Obj(argList[0], argList);
   Base_Cmd* object2= new Cmd_Obj(argList2[0], argList2);

   Base_Cmd* andConnect= new And(object1, object2);  
   
   EXPECT_EQ(andConnect->doWork(), false);  //returns false since 2nd command fails
}

#endif

#ifndef __OR_TEST_HPP__
#define __OR_TEST_HPP__

#include "../header/or.hpp"

TEST(OrTestSet, twoCommandSuccessTest) {
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

   Base_Cmd* andConnect= new Or(object1, object2);  
   
   EXPECT_EQ(andConnect->doWork(), false);    //returns false since first command is succesful

}

TEST(OrTestSet, FirstCommandFailsTest) {
   char* argList[5];  
   argList[0]="eho";
   argList[1]="first";
   argList[2]="command";
   argList[3]="executed";
   argList[4]=NULL;
  
   char* argList2[2];
   argList2[0]="ls";
   argList2[1]=NULL;


   Base_Cmd* object1= new Cmd_Obj(argList[0], argList);
   Base_Cmd* object2= new Cmd_Obj(argList[0], argList2);

   Base_Cmd* andConnect= new Or(object1, object2);  
   
   EXPECT_EQ(andConnect->doWork(), false);  //returns true since 1st command fails and 2nd command is executed

}
TEST(OrTestSet, SecondCommandFailsTest) {
   char* argList[5];  
   argList[0]="echo";
   argList[1]="first";
   argList[2]="command";
   argList[3]="executed";
   argList[4]=NULL;
  
   char* argList2[2];
   
   argList2[0]="s";
   argList2[1]=NULL;


   Base_Cmd* object1= new Cmd_Obj(argList[0], argList);
   Base_Cmd* object2= new Cmd_Obj(argList2[0], argList2);

   Base_Cmd* andConnect= new Or(object1, object2);  
   
   EXPECT_EQ(andConnect->doWork(), false);  //returns false since 1st command succeeds
}

#endif

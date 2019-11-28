#ifndef __INTERFACE_TEST_HPP__
#define __INTERFACE_TEST_HPP__

#include "../header/interface.hpp"

TEST(InterfaceTestSet, simpleCommands){
	Interface test;

	char* arg1 = "echo hello";
	char* arg2 = "cd ../";
	char* arg3 = "ec no";
	char* arg4 = "ls -all";

	test.setCommand(arg1);
	EXPECT_EQ(test.doWork(), true);

	test.setCommand(arg2);
	EXPECT_EQ(test.doWork(), true);

	test.setCommand(arg3);
	EXPECT_EQ(test.doWork(), false);

	test.setCommand(arg4);
	EXPECT_EQ(test.doWork(), true);

}


TEST(InterfaceTestSet, multiCommands){
	Interface test;

	char* arg1 = "echo hello && echo goodbye";
	char* arg2 = "ech whoa || echo passed";
	char* arg3 = "not yes || echo why";
	char* arg4 = "ec all || ec no && echo yes"; 



	test.setCommand(arg1);
	EXPECT_EQ(test.doWork(), true);

	test.setCommand(arg2);
	EXPECT_EQ(test.doWork(), true);

	test.setCommand(arg3);
	EXPECT_EQ(test.doWork(), true);

	test.setCommand(arg4);
	EXPECT_EQ(test.doWork(), false);
}

#endif

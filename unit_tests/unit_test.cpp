#include "gtest/gtest.h"

#include "../unit_tests/io_cmd_test.hpp"
#include "../unit_tests/pipe_cmd_test.hpp"
//#include "../unit_tests/and_test.hpp"
//#include "../unit_tests/cmd_obj_test.hpp"
//#include "../unit_tests/test_cmd_test.hpp"
//#include "../unit_tests/semicolon_test.hpp"
//#include "../unit_tests/or_test.hpp"
//#include "../unit_tests/interface_test.hpp"

int main(int argc, char **argv) {
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}

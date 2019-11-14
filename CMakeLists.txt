CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

ADD_SUBDIRECTORY(googletest)

SET(CMAKE_CXX_STANDARD 11)

SET(UNIT_TESTS 
      unit_tests/unit_test.cpp 
      unit_tests/co_dowork_test.hpp
)

ADD_LIBRARY(src
   src/cmd_obj_dowork.cpp
)

ADD_EXECUTABLE( test
   unit_tests/unit_test.cpp 
)

TARGET_INCLUDE_DIRECTORIES(test
   PRIVATE
      ${PROJECT_SOURCE_DIR}/unit_tests     
)

TARGET_INCLUDE_DIRECTORIES(test 
   PRIVATE
      ${PROJECT_SOURCE_DIR}/src
)

TARGET_LINK_LIBRARIES(test gtest src)
TARGET_COMPILE_DEFINITIONS(test PRIVATE gtest_disable_pthreads=ON)

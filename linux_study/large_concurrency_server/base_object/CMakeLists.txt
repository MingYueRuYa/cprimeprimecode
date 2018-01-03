# cmake_mininum_required(VERSION 2.6)

set(CXX_FLAGS -g -Wall)
set(CMAKE_CXX_COMPILE "g++")
string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_executable(bf_test bf_test.cpp)

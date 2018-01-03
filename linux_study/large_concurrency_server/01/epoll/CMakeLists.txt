project(pas CXX)

set(CXX_FLAGS -g -Wall)
set(CMAKE_CXX_COMPILER "g++")
string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}")

set(EXECUTETABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_executable(echoepoll echoepoll.cpp)
add_executable(echocli echocli.cpp)

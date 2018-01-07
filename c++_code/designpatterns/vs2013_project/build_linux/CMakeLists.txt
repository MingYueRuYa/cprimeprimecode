set(base_SRCS
    ../source/abstract_factory.cpp
    ../source/adapter.cpp
    ../source/bridge.cpp
    ../source/builder.cpp
    ../source/chain_of_responsibility.cpp
    ../source/command.cpp
    ../source/composite.cpp
    ../source/decorator.cpp
    ../source/designpatternpack.h
    ../source/facade.cpp
    ../source/factory.cpp
    ../source/flyweight.cpp
    ../source/iterator.cpp
    ../source/main.cpp
    ../source/mediator.cpp
    ../source/memento.cpp
    ../source/observer_event.cpp
    ../source/prototype.cpp
    ../source/proxy.cpp
    ../source/simple_factory.cpp
    ../source/singleton.cpp
    ../source/state.cpp
    ../source/state.h
    ../source/stateimpl.cpp
    ../source/strategy.cpp
    ../source/template.cpp
    ../source/visitor.cpp
)

set(CXX_FLAGS
    -g 
    -Wall
    -std=c++11)


include(CheckCXXCompilerFlag)  
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)  
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)  
if(COMPILER_SUPPORTS_CXX11)  
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")  
elseif(COMPILER_SUPPORTS_CXX0X)  
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")  
else()  
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")  
endif()  


set(CMAKE_CXX_COMPILER "g++")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_executable(app ${base_SRCS})

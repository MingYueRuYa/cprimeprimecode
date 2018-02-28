set(base_SRCS
	08_prevent_exceptions_from_leaving_destructors.cpp
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

add_executable(03_use_const_whenever_possible
	03_use_const_whenever_possible.cpp)

add_executable(08_prevent_exceptions_from_leaving_destructors
	08_prevent_exceptions_from_leaving_destructors.cpp)

add_executable(13_user_objects_to_manager_resource
	13_user_objects_to_manager_resource.cpp)

add_executable(25_consider_support_for_a_non_throwing_swap
	25_consider_support_for_a_non_throwing_swap.cpp)

add_executable(49_understand_the_behavior_of_new_handler
	49_understand_the_behavior_of_new_handler.cpp)

add_executable(51_adhere_to_convention_when_writing_new_and_delete
	51_adhere_to_convention_when_writing_new_and_delete.cpp)

add_executable(52_write_placement_delete_if_you_write_placement_new
	52_write_placement_delete_if_you_write_placement_new.cpp)

add_executable(54_familiarize_yourself_with_the_stl
	54_familiarize_yourself_with_the_stl.cpp)

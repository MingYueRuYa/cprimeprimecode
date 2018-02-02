add_executable(bsa bsa.cc)

add_executable(pthread_atfork_test pthread_atfork_test.cc)
target_link_libraries(pthread_atfork_test pthread)

add_executable(CountDownLatch_test1 CountDownLatch_test1.cc)
target_link_libraries(CountDownLatch_test1 muduo_base)

add_executable(CountDownLatch_test2 CountDownLatch_test2.cc)
target_link_libraries(CountDownLatch_test2 muduo_base)

add_executable(deadlock_test1 deadlock_test1.cc)
target_link_libraries(deadlock_test1 pthread)

add_executable(deadlock_test2 deadlock_test2.cc)
target_link_libraries(deadlock_test2 pthread)

add_executable(Log_test1 Log_test1.cc)
target_link_libraries(Log_test1 muduo_base)

add_executable(Log_test2 Log_test2.cc)
target_link_libraries(Log_test2 muduo_base)

add_executable(Reactor_test01 Reactor_test01.cc)
target_link_libraries(Reactor_test01 muduo_net)

add_executable(Reactor_test02 Reactor_test02.cc)
target_link_libraries(Reactor_test02 muduo_net)

add_executable(Reactor_test03 Reactor_test03.cc)
target_link_libraries(Reactor_test03 muduo_net)

add_executable(Reactor_test04 Reactor_test04.cc)
target_link_libraries(Reactor_test04 muduo_net)

add_executable(Reactor_test05 Reactor_test05.cc)
target_link_libraries(Reactor_test05 muduo_net)

add_executable(Reactor_test06 Reactor_test06.cc)
target_link_libraries(Reactor_test06 muduo_net)

add_executable(Test_lower_bound_upper_bound 
				Test_lower_bound_upper_bound.cpp)
target_link_libraries(Test_lower_bound_upper_bound muduo_net)

add_executable(rov rov.cpp)

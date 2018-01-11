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


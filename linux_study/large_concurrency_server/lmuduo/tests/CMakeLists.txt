add_executable(bsa bsa.cc)

add_executable(pthread_atfork_test pthread_atfork_test.cc)
target_link_libraries(pthread_atfork_test pthread)

add_executable(deadlock_test1 deadlock_test1.cc)
target_link_libraries(deadlock_test1 pthread)

add_executable(deadlock_test2 deadlock_test2.cc)
target_link_libraries(deadlock_test2 pthread)

add_executable(atomic_unittest Atomic_unittest.cc)
target_link_libraries(atomic_unittest muduo_base)

add_executable(Mutex_test Mutex_test.cc)
target_link_libraries(Mutex_test muduo_base)

add_executable(Exception_test Exception_test.cc)
target_link_libraries(Exception_test muduo_base)

add_executable(Thread_test Thread_test.cc)
target_link_libraries(Thread_test muduo_base)

add_executable(timestamp_unittest Timestamp_unittest.cc)
target_link_libraries(timestamp_unittest muduo_base)


project(thread_pool)

add_executable(thread_pool thread_pool.cpp)
target_link_libraries(thread_pool PRIVATE pthread)

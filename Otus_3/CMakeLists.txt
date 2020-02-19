cmake_minimum_required(VERSION 3.5)

project ("Otus_2" VERSION 0.0.1) 

set(ALLOCATOR_SRC "my_allocator.h")
set(FACTORIAL_SRC "factorial.h")
set(LIST_SRC "my_list.h")

add_executable(Otus_3 otus_3.cpp ${ALLOCATOR_SRC} ${FACTORIAL_SRC} ${LIST_SRC})
set_target_properties(Otus_3 PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
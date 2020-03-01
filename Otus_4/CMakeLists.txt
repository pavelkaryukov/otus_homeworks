cmake_minimum_required (VERSION 3.8)

project ("Otus_2" VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER}) 

add_executable(Otus_4 otus_4.cpp "ip_to_str.h" "tuple_utils.h")
set_target_properties(Otus_4 PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
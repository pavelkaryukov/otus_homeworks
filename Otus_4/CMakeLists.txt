cmake_minimum_required (VERSION 3.8)

project ("Otus_2" VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER}) 

set(IP_STR "ip_to_str.h")

add_executable(Otus_4 otus_4.cpp ${IP_STR})
set_target_properties(Otus_4 PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
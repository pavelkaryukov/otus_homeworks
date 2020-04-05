cmake_minimum_required (VERSION 3.8)

project ("Otus_6" VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER}) 

add_executable(matrix otus_6.cpp) 


set_target_properties (
	matrix PROPERTIES 
	CXX_STANDARD 11
	CXX_STANDARD_REQUIRED ON	
)

find_package(Boost REQUIRED)
if(NOT Boost_FOUND)
	message(SEND_ERROR "Failed to find boost")
	return()
endif()

target_include_directories(matrix PRIVATE ${Boost_INCLUDE_DIRS})

cmake_minimum_required (VERSION 3.8)

project ("Otus_9" VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER}) 

add_executable(bayan otus_9.cpp) 

set_target_properties (
	bayan PROPERTIES 
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON	
)

find_package(Boost REQUIRED)
if(NOT Boost_FOUND)
	message(SEND_ERROR "Failed to find boost")
	return()
endif()

target_link_libraries(bayan PRIVATE $<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9.0>>:stdc++fs>)
target_include_directories(
	bayan
	PRIVATE
	${PROJECT_SOURCE_DIR}
	${Boost_INCLUDE_DIRS}
)
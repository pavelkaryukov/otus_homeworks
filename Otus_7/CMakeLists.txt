cmake_minimum_required (VERSION 3.8)

project ("Otus_7" VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER}) 
set(CMD_SRC     "command/icommand.h" "command/simple_command.h")
set(DISPATCHER_SRC     "dispatcher/dispatcher.h" "dispatcher/logger.h")

add_executable(bulk otus_7.cpp ${CMD_SRC} ${DISPATCHER_SRC}) 

set_target_properties (
	bulk PROPERTIES 
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON	
)

find_package(Boost REQUIRED)
if(NOT Boost_FOUND)
	message(SEND_ERROR "Failed to find boost")
	return()
endif()

target_include_directories(
	bulk
	PRIVATE
	${PROJECT_SOURCE_DIR}
	${Boost_INCLUDE_DIRS}
)
cmake_minimum_required (VERSION 3.8)

project ("Otus_10" VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER}) 
set(CMD_SRC     "command/icommand.h" "command/simple_command.h")
set(DISPATCHER_SRC     "dispatcher/dispatcher.h")
set(LOG_SRC "logger/logger.h" "logger/logger_screen.h" "logger/logger_file.h")
set(CONCURRENT_SRC     "concurrent/concurrent_deque.h")

add_executable(bulkmt otus_10.cpp ${CMD_SRC} ${DISPATCHER_SRC} ${CONCURRENT_SRC}) 

set_target_properties (
	bulkmt PROPERTIES 
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON	
)

find_package(Boost REQUIRED)
if(NOT Boost_FOUND)
	message(SEND_ERROR "Failed to find boost")
	return()
endif()


Find_package(Threads)
if (Threads_FOUND)
	#target_link_libraries(bulkmt ${CMAKE_THREAD_LIBS_INIT})	
endif()

target_link_libraries(bulkmt  ${CMAKE_THREAD_LIBS_INIT} PRIVATE $<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9.0>>:stdc++fs>)


target_include_directories(
	bulkmt
	PRIVATE
	${PROJECT_SOURCE_DIR}
	${Boost_INCLUDE_DIRS}
)
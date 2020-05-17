cmake_minimum_required (VERSION 3.8)

project ("Otus_11" VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER}) 
#dispatcher block

set(CMD_SRC            "lib/dispatcher/command/icommand.h" 
                       "lib/dispatcher/command/simple_command.h")
set(LOG_SRC            "lib/dispatcher/logger/logger.h" 
                       "lib/dispatcher/logger/logger_screen.h" 
                       "lib/dispatcher/logger/logger_file.h")
set(CONCURRENT_SRC     "lib/dispatcher/concurrent/concurrent_deque.h")
set(DISPATCHER_SRC     "lib/dispatcher/dispatcher.h" ${CONCURRENT_SRC} ${LOG_SRC} ${CMD_SRC})   
#\dispatcher block

set(ASYNC_LIB_SRC "lib/bulk_async.h" "lib/bulk_async.cpp" ${DISPATCHER_SRC})

add_library(libasync ${ASYNC_LIB_SRC})

set_target_properties (
	libasync PROPERTIES 
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON	
)

find_package(Boost REQUIRED)
if(NOT Boost_FOUND)
	message(SEND_ERROR "Failed to find boost")
	return()
endif()


Find_package(Threads)

target_link_libraries(libasync  ${CMAKE_THREAD_LIBS_INIT}  $<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9.0>>:stdc++fs>)


target_include_directories(
	libasync
	PRIVATE
	${PROJECT_SOURCE_DIR}/lib/dispatcher
	${PROJECT_SOURCE_DIR}
	${Boost_INCLUDE_DIRS}
)

##################################
##########TEST_BLOCK##############
add_executable(bulk_async_test "test/main.cpp" ) 

set_target_properties (
	bulk_async_test PROPERTIES 
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON	
)

target_include_directories(			
	bulk_async_test
	PRIVATE
	${PROJECT_SOURCE_DIR}
	${PROJECT_SOURCE_DIR}/lib
)

target_link_libraries(bulk_async_test ${CMAKE_THREAD_LIBS_INIT} libasync $<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9.0>>:stdc++fs>)


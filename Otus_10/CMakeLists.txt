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

target_link_libraries(bulkmt  ${CMAKE_THREAD_LIBS_INIT}  $<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9.0>>:stdc++fs>)


target_include_directories(
	bulkmt
	PRIVATE
	${PROJECT_SOURCE_DIR}
	${Boost_INCLUDE_DIRS}
)

### TEST
#Google Test
find_package(GTest REQUIRED)

if(NOT GTEST_FOUND )
	message(SEND_ERROR "Failed to find GTest")
	return()
endif()

set(TESTS_SRC "test")
add_executable(test_bulkmt ${TESTS_SRC}/gtest_bulkmt.cpp ${CMD_SRC} ${DISPATCHER_SRC} ${CONCURRENT_SRC})

set_target_properties (
	test_bulkmt  PROPERTIES 
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON	
)
Find_package(Threads)

target_link_libraries(test_bulkmt 
	${GTEST_BOTH_LIBRARIES} 
	${CMAKE_THREAD_LIBS_INIT}  
	$<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9.0>>:stdc++fs>
	)



target_include_directories(			
	test_bulkmt
	PRIVATE
	${GTEST_INCLUDE_DIRS}
	${PROJECT_SOURCE_DIR}
	${Boost_INCLUDE_DIRS}
)
enable_testing()
add_test(test_bulkmt test_bulkmt)

install(TARGETS bulkmt DESTINATION bin)
set(CPACK_PACKAGE_NAME "OtusHomeworks")
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_VENDOR "Karyukov")
set(CPACK_PACKAGE_CONTACT "pavelkaryukov@gmail.com")
include (CPack)

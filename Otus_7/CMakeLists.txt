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

target_link_libraries(bulk PRIVATE $<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9.0>>:stdc++fs>)
target_include_directories(
	bulk
	PRIVATE
	${PROJECT_SOURCE_DIR}
	${Boost_INCLUDE_DIRS}
)

#Google Test
find_package(GTest REQUIRED)

if(NOT GTEST_FOUND )
	message(SEND_ERROR "Failed to find GTest")
	return()
endif()

set(TESTS_SRC "test")
add_executable(test_bulk ${TESTS_SRC}/gtest_bulk.cpp ${CMD_SRC} ${DISPATCHER_SRC})

set_target_properties (
	test_bulk  PROPERTIES 
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON	
)

target_link_libraries(test_bulk ${GTEST_BOTH_LIBRARIES} $<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9.0>>:stdc++fs>)

Find_package(Threads)
if (Threads_FOUND)
	target_link_libraries(test_bulk ${CMAKE_THREAD_LIBS_INIT})	
endif()

target_include_directories(			
	test_bulk
	PRIVATE
	${GTEST_INCLUDE_DIRS}
	${PROJECT_SOURCE_DIR}
	${Boost_INCLUDE_DIRS}
)
enable_testing()
add_test(test_bulk test_bulk)

install(TARGETS bulk DESTINATION bin)
set(CPACK_PACKAGE_NAME "OtusHomeworks")
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_VENDOR "Karyukov")
set(CPACK_PACKAGE_CONTACT "pavelkaryukov@gmail.com")
include (CPack)
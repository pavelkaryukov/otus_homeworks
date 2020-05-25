cmake_minimum_required (VERSION 3.8)

project ("Otus_13" VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER}) 

set(RSUBD_SRC     
    "rsubd/cmd_performer.h" "rsubd/code_result.h" "rsubd/cortej.h"
     "rsubd/my_table.h" "rsubd/rsubd.h"
)
set(DISPATCHER_SRC     "dispatcher/dispatcher.h")

set(CONCURRENT_SRC     "concurrent/concurrent_deque.h")


add_executable(join_server main.cpp ${RSUBD_SRC} ${DISPATCHER_SRC} ${CONCURRENT_SRC})
set_target_properties (
	join_server 
	PROPERTIES 
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON	
)

find_package(Boost COMPONENTS system REQUIRED)
if(NOT Boost_FOUND)
	message(SEND_ERROR "Failed to find boost")
	return()
endif()
 
Find_package(Threads)

target_include_directories(join_server PRIVATE  ${PROJECT_SOURCE_DIR} ${Boost_INCLUDE_DIRS})
target_link_libraries(join_server  
    ${Boost_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}  
    $<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9.0>>:stdc++fs>
)

####################################################
##################_TEST_BLOCK_######################
find_package(GTest REQUIRED)
if(NOT GTEST_FOUND )
	message(SEND_ERROR "Failed to find GTest")
	return()
endif()

add_executable(test_join "test/test_join.cpp" ${RSUBD_SRC} ${DISPATCHER_SRC} ${CONCURRENT_SRC})

set_target_properties (
	test_join  PROPERTIES 
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON	
)

target_include_directories(test_join PRIVATE  ${GTEST_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR} ${Boost_INCLUDE_DIRS})

target_link_libraries(test_join  
    ${Boost_LIBRARIES}
    ${GTEST_BOTH_LIBRARIES} 
    ${CMAKE_THREAD_LIBS_INIT}  
    $<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9.0>>:stdc++fs>
)

enable_testing()
add_test(test_join test_join)

####################################################
################_INSTALL_BLOCK_#####################
install(TARGETS join_server DESTINATION bin)
set(CPACK_PACKAGE_NAME "OtusHomeworks")
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_VENDOR "Karyukov")
set(CPACK_PACKAGE_CONTACT "pavelkaryukov@gmail.com")
include (CPack)
cmake_minimum_required (VERSION 3.8)

project ("Otus_14" VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER}) 
set(SPLIT_SRC "file_splitter/file_splitter.h" "file_splitter/file_splitter.cpp")
set(MAP_REDUCE_SRC "map_reduce/map_reduce.h")
set(MAPPER_SRC "mapper/my_mapper.h"  "mapper/hasher/ihasher.h" "mapper/hasher/hasher_string.h" "mapper/hasher/hasher_crc32.h")
set(PREFIX_SRC "prefix_finder/prefix_finder.h")
set(REDUCER_SRC "reducer/reducer.h")

add_executable(yamr main.cpp ${SPLIT_SRC} ${MAP_REDUCE_SRC} ${MAPPER_SRC} ${PREFIX_SRC} ${REDUCER_SRC}) 
set_target_properties (
	yamr 
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

target_include_directories(yamr PRIVATE  ${PROJECT_SOURCE_DIR} ${Boost_INCLUDE_DIRS})
target_link_libraries(yamr  
    ${Boost_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}  
    $<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9.0>>:stdc++fs>
)

####################################################
##################_TEST_BLOCK_######################
set (TEST_FILE_PATH ${PROJECT_SOURCE_DIR}/../ip_database/test.csv)
file(COPY ${TEST_FILE_PATH}
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

find_package(GTest REQUIRED)
if(NOT GTEST_FOUND )
	message(SEND_ERROR "Failed to find GTest")
	return()
endif()

add_executable(test_yamr "test/test_yamr.cpp" ${SPLIT_SRC} ${MAP_REDUCE_SRC} ${MAPPER_SRC} ${PREFIX_SRC} ${REDUCER_SRC})

set_target_properties (
	test_yamr  PROPERTIES 
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON	
)

target_include_directories(test_yamr PRIVATE  ${GTEST_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR} ${Boost_INCLUDE_DIRS})

target_link_libraries(test_yamr  
    ${GTEST_BOTH_LIBRARIES} 
    ${CMAKE_THREAD_LIBS_INIT}  
    $<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9.0>>:stdc++fs>
)

enable_testing()
add_test(test_yamr test_yamr)


####################################################
################_INSTALL_BLOCK_#####################
install(TARGETS yamr DESTINATION bin)
set(CPACK_PACKAGE_NAME "OtusHomeworks")
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_VENDOR "Karyukov")
set(CPACK_PACKAGE_CONTACT "pavelkaryukov@gmail.com")
include (CPack)
cmake_minimum_required (VERSION 3.8)

project ("Otus_9" VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER}) 

set(HASH_SRC "hash/ihash.h" "hash/hash_crc32.h" "hash/hash_md5.h")
set(FILECONTROL_SRC "file/file_hash.h" "file/file_filter.h" "file/file_border.h" "file/dir_border.h")
set(FINDER_SRC "duplicate/duplicate_finder.h")
add_executable(bayan otus_9.cpp "args/cmd_args.h" ${HASH_SRC} ${FILECONTROL_SRC} ${FINDER_SRC}) 

set_target_properties (
	bayan PROPERTIES 
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON	
)
find_package(Boost COMPONENTS program_options filesystem regex REQUIRED)
if(NOT Boost_FOUND)
	message(SEND_ERROR "Failed to find boost")
	return()
endif()

target_link_libraries(bayan  ${Boost_LIBRARIES}) 

target_include_directories(
	bayan
	PRIVATE
	${PROJECT_SOURCE_DIR}
	${Boost_INCLUDE_DIRS}
)

set(TEST_FILE_PATH test_catalog/file_1.txt test_catalog/file_2.txt test_catalog/file_3.txt test_catalog/file_4.txt 
test_catalog/file_1.lib test_catalog/file_2.lib test_catalog/file_3.lib test_catalog/file_4.lib
)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/test_catalog)

file(COPY ${TEST_FILE_PATH}
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/test_catalog)

#Google Test
find_package(GTest REQUIRED)

if(NOT GTEST_FOUND )
	message(SEND_ERROR "Failed to find GTest")
	return()
endif()

set(TESTS_SRC "test")
add_executable(test_bayan ${TESTS_SRC}/gtest_bayan.cpp  ${HASH_SRC} ${FILECONTROL_SRC} ${FINDER_SRC})
set_target_properties (
	test_bayan  PROPERTIES 
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON	
)

target_link_libraries(test_bayan ${GTEST_BOTH_LIBRARIES} ${Boost_LIBRARIES}) 

Find_package(Threads)
if (Threads_FOUND)
	target_link_libraries(test_bayan ${CMAKE_THREAD_LIBS_INIT})	
endif()

target_include_directories(			
	test_bayan
	PRIVATE
	${GTEST_INCLUDE_DIRS}
	${PROJECT_SOURCE_DIR}
	${Boost_INCLUDE_DIRS}
)
enable_testing()
add_test(test_bayan test_bayan)



install(TARGETS bayan DESTINATION bin)
set(CPACK_PACKAGE_NAME "OtusHomeworks")
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_VENDOR "Karyukov")
set(CPACK_PACKAGE_CONTACT "pavelkaryukov@gmail.com")
include (CPack)
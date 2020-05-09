cmake_minimum_required (VERSION 3.8)

project ("Otus_2" VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER}) 

add_executable(print_ip otus_4.cpp "ip_to_str.h" "tuple_utils.h")
set_target_properties(print_ip PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

set(TESTS_SRC "tests")
#Google Test
find_package(GTest REQUIRED)

if(NOT GTEST_FOUND )
	message(SEND_ERROR "Failed to find GTest")
	return()
endif()

add_executable(gtest_print_ip ${TESTS_SRC}/gtest_otus4.cpp "ip_to_str.h")
set_target_properties (
	gtest_print_ip PROPERTIES 
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON	
)

target_link_libraries(gtest_print_ip 
	${GTEST_BOTH_LIBRARIES} 	
)

Find_package(Threads)
if (Threads_FOUND)
	target_link_libraries(gtest_print_ip ${CMAKE_THREAD_LIBS_INIT})	
endif()

target_include_directories(
	gtest_print_ip
	PRIVATE
	${GTEST_INCLUDE_DIRS}
	${PROJECT_SOURCE_DIR}
)


enable_testing()
add_test(gtest_print_ip gtest_print_ip)

install(TARGETS print_ip DESTINATION bin)
set(CPACK_PACKAGE_NAME "OtusHomeworks")
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_VENDOR "Karyukov")
set(CPACK_PACKAGE_CONTACT "pavelkaryukov@gmail.com")
include (CPack)


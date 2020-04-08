cmake_minimum_required (VERSION 3.8)

project ("Otus_6" VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER}) 

add_executable(matrix otus_6.cpp matrix.h) 


set_target_properties (
	matrix PROPERTIES 
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON	
)

find_package(Boost REQUIRED)
if(NOT Boost_FOUND)
	message(SEND_ERROR "Failed to find boost")
	return()
endif()

set(TESTS_SRC "tests")
#Google Test
find_package(GTest REQUIRED)

if(NOT GTEST_FOUND )
	message(SEND_ERROR "Failed to find GTest")
	return()
endif()
target_include_directories(matrix PRIVATE ${Boost_INCLUDE_DIRS})


add_executable(test_matrix ${TESTS_SRC}/gtest_matrix.cpp matrix.h)
set_target_properties (
	test_matrix PROPERTIES 
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON	
)

target_link_libraries(test_matrix 
	${GTEST_BOTH_LIBRARIES} 	
)

Find_package(Threads)
if (Threads_FOUND)
	target_link_libraries(test_matrix ${CMAKE_THREAD_LIBS_INIT})	
endif()

target_include_directories(
	test_matrix
	PRIVATE
	${GTEST_INCLUDE_DIRS}
	${PROJECT_SOURCE_DIR}
	${Boost_INCLUDE_DIRS}
)
enable_testing()
add_test(test_matrix test_matrix)

install(TARGETS matrix DESTINATION bin)
set(CPACK_PACKAGE_NAME "OtusHomeworks")
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_VENDOR "Karyukov")
set(CPACK_PACKAGE_CONTACT "pavelkaryukov@gmail.com")
include (CPack)
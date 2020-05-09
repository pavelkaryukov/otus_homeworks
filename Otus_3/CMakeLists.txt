cmake_minimum_required(VERSION 3.5)

project ("Otus_3" VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER}) 

set(ALLOCATOR_SRC "my_allocator.h")
set(FACTORIAL_SRC "factorial.h")
set(LIST_SRC "my_list.h")
set(OTUS_SRC "otus.h")
set(TESTS_SRC "tests")

add_executable(Otus_3 otus_3.cpp ${ALLOCATOR_SRC} ${FACTORIAL_SRC} ${LIST_SRC} ${OTUS_SRC})
set_target_properties(Otus_3 PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

#Google Test
find_package(GTest REQUIRED)

if(NOT GTEST_FOUND )
	message(SEND_ERROR "Failed to find GTest")
	return()
endif()

add_executable(gtest_test_otus3 ${TESTS_SRC}/gtest_test_otus3.cpp ${OTUS_SRC})
set_target_properties (
	gtest_test_otus3 PROPERTIES 
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON	
)

target_link_libraries(gtest_test_otus3 
	${GTEST_BOTH_LIBRARIES} 	
)

find_package(Threads)
if (Threads_FOUND)
	target_link_libraries(gtest_test_otus3 ${CMAKE_THREAD_LIBS_INIT})	
endif()

target_include_directories(
	gtest_test_otus3
	PRIVATE
	${GTEST_INCLUDE_DIRS}
	${PROJECT_SOURCE_DIR}/${MYSTR_FOLDER}
)

target_include_directories(
	gtest_test_otus3
	PRIVATE
	${GTEST_INCLUDE_DIRS}
)

enable_testing()
add_test(gtest_test_otus3 gtest_test_otus3)
#Сборка пакета
#Не забудь её как нибудь вынести
install(TARGETS Otus_3 DESTINATION bin)
set(CPACK_PACKAGE_NAME "OtusHomeworks")
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_VENDOR "Karyukov")
set(CPACK_PACKAGE_CONTACT "pavelkaryukov@gmail.com")
include (CPack)
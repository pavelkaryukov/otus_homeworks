cmake_minimum_required (VERSION 3.8)

project ("Otus_2" VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER}) 

set (BIN_POW_SRC   "bin_pow/bin_pow.cpp" "bin_pow/bin_pow.h")
set (IP_FILTER_SRC "ip_filter/ip_filter.cpp" "ip_filter/ip_filter.h")
set (MD5_SRC "md5/md5.cpp" "md5/md5.h")#Заменить на lib файд
set (MYSTR_FOLDER "my_str")
set (MYSTR_SRC ${MYSTR_FOLDER}/my_str.cpp ${MYSTR_FOLDER}/my_str.h)
set (TEST_FILE_PATH ${PROJECT_SOURCE_DIR}/examples/ip_filter-12995-758870.tsv)

file(COPY ${TEST_FILE_PATH}
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
add_library(mystr STATIC ${MYSTR_SRC}) 							
add_library(md5sum STATIC ${MD5_SRC})
add_library(binpow STATIC ${BIN_POW_SRC})
#библиотеки
set_target_properties (
	mystr 
	md5sum
	binpow
	PROPERTIES 
	CXX_STANDARD 17 
	CXX_STANDARD_REQUIRED ON	
)

set_target_properties (
	mystr PROPERTIES 
	CXX_STANDARD 17 
	CXX_STANDARD_REQUIRED ON	
)


add_executable(Otus_2 "otus_2.cpp" ${IP_FILTER_SRC} ${TESTS_SRC}) 
target_include_directories(Otus_2 PUBLIC ${PROJECT_SOURCE_DIR}/${MYSTR_FOLDER} ${CMAKE_CURRENT_BINARY_DIR} ${TEST_FILE_PATH})

target_link_libraries(Otus_2 
	mystr 
	md5sum 
	binpow
)

set_target_properties (
	Otus_2
	PROPERTIES 
	CXX_STANDARD 17 
	CXX_STANDARD_REQUIRED ON	
)

#Test 
set(TESTS_SRC "tests/boost_test.cpp")

#Boost Test
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

if(NOT Boost_FOUND)
	message(SEND_ERROR "Failed to find boost")
	return()
endif()

add_executable(boost_test ${TESTS_SRC} ${IP_FILTER_SRC})

set_target_properties (
	boost_test PROPERTIES 
	CXX_STANDARD 17 
	CXX_STANDARD_REQUIRED ON	
)

target_include_directories(
	boost_test
	PRIVATE
	${CMAKE_CURRENT_BINARY_DIR}	
	${Boost_INCLUDE_DIR}
	${PROJECT_SOURCE_DIR}/${MYSTR_FOLDER}
)

target_link_libraries(boost_test
    ${Boost_LIBRARIES}
	mystr
	md5sum
	binpow
)

if (NOT MSVC)
  	set_target_properties(boost_test PROPERTIES
		COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
	)
endif()

enable_testing()
add_test(boost_test boost_test)

#Сборка пакета
install(TARGETS Otus_2 DESTINATION bin)
set(CPACK_PACKAGE_NAME "OtusHomeworks")
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_VENDOR "Karyukov")
set(CPACK_PACKAGE_CONTACT "pavelkaryukov@gmail.com")
include (CPack)



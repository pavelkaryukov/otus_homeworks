cmake_minimum_required (VERSION 3.8)

project ("Otus_12" VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER}) 
set(ASYNC_LIB_DIR ${CMAKE_BINARY_DIR}/../Otus_11/)		 

add_executable(bulk_server main.cpp)
set_target_properties (
	bulk_server 
	PROPERTIES 
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON	
)

find_package(Boost COMPONENTS system REQUIRED)
find_package(Threads)

target_include_directories(	bulk_server 
	PRIVATE 
	${CMAKE_BINARY_DIR}/Otus_11 
	${Boost_INCLUDE_DIR}
)

IF (WIN32)
	set(ASYNC_LIB_PATH ${CMAKE_BINARY_DIR}/Otus_11/libasync.lib)
  # set stuff for windows
ELSE()

	set(ASYNC_LIB_PATH ${CMAKE_BINARY_DIR}/Otus_11/libasync.a)
  # set stuff for other systems
ENDIF()

target_link_libraries(bulk_server
        ${Boost_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT}
		${ASYNC_LIB_PATH}# учитывать возможность a файла 
)

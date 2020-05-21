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

#find_library (CURL_LIBRARY NAMES libasync  HINTS ${PROJECT_SOURCE_DIR}/lib)
IF (WIN32)
	set(ASYNC_LIB_PATH ${PROJECT_SOURCE_DIR}/lib/libasync.lib)	
ELSE()
	set(ASYNC_LIB_PATH ${PROJECT_SOURCE_DIR}/lib/libasync.a)
#	#set(ASYNC_LIB_PATH ${CMAKE_BINARY_DIR}/Otus_11/libasync_static.a)
#	#set (CURL_LIBRARY ${CMAKE_BINARY_DIR}/Otus_11/liblibasync.a)
#	  # set stuff for other systems
ENDIF()
message("------------\r\n"  ${CURL_LIBRARY} "------------\r\n")

target_link_libraries(bulk_server
        ${Boost_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT}
		${ASYNC_LIB_PATH}# учитывать возможность a файла 
)

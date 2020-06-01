cmake_minimum_required (VERSION 3.8)

project ("Otus_14" VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER}) 
set(SPLIT_SRC "file_splitter/file_splitter.h" "file_splitter/file_splitter.cpp")
add_executable(map_reduce main.cpp ${SPLIT_SRC})
set_target_properties (
	map_reduce 
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

target_include_directories(map_reduce PRIVATE  ${PROJECT_SOURCE_DIR} ${Boost_INCLUDE_DIRS})
target_link_libraries(map_reduce  
    ${Boost_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}  
    $<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9.0>>:stdc++fs>
)
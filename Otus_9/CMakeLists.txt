cmake_minimum_required (VERSION 3.8)

project ("Otus_9" VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER}) 

set(HASH_SRC "hash/ihash.h" "hash/hash_crc32.h" "hash/hash_md5.h")
set(FILECONTROL_SRC "file/file_hash.h" "file/file_filter.h")
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

target_link_libraries(bayan  ${Boost_LIBRARIES}) #PRIVATE $<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9.0>>:stdc++fs>
target_include_directories(
	bayan
	PRIVATE
	${PROJECT_SOURCE_DIR}
	${Boost_INCLUDE_DIRS}
)
cmake_minimum_required (VERSION 3.8)

project ("Otus_2" VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER}) 

set (ACM_TIMUS_SRC "acm_timus/acm_timus.cpp" "acm_timus/acm_timus.h")
set (BIN_POW_SRC   "bin_pow/bin_pow.cpp" "bin_pow/bin_pow.h")
set (IP_FILTER_SRC "ip_filter/ip_filter.cpp" "ip_filter/ip_filter.h")

set (MYSTR_FOLDER "my_str")
set (MYSTR_SRC ${MYSTR_FOLDER}/my_str.cpp ${MYSTR_FOLDER}/my_str.h)
add_library(mystr STATIC ${MYSTR_SRC}) 

set_target_properties (
	mystr PROPERTIES 
	CXX_STANDARD 17 
	CXX_STANDARD_REQUIRED ON	
)
add_executable(Otus_2 "otus_2.cpp" ${ACM_TIMUS_SRC} ${BIN_POW_SRC} ${IP_FILTER_SRC}) 
message("PROJECT_SOURCE_DIR = " ${PROJECT_SOURCE_DIR})
#message("CURRENT_SOURCE_DIR = " ${CURRENT_SOURCE_DIR})
target_include_directories(Otus_2 PUBLIC ${PROJECT_SOURCE_DIR})

target_link_libraries(Otus_2 mystr)
set_target_properties (
	Otus_2 PROPERTIES 
	CXX_STANDARD 17 
	CXX_STANDARD_REQUIRED ON	
)

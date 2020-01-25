cmake_minimum_required (VERSION 3.8)

project ("Otus_2" VERSION 0.0.1) 

set (ACM_TIMUS_SRC "acm_timus/acm_timus.cpp" "acm_timus/acm_timus.h")
set (BIN_POW_SRC   "bin_pow/bin_pow.cpp" "bin_pow/bin_pow.h")

add_executable(Otus_2 "otus_2.cpp" ${ACM_TIMUS_SRC} ${BIN_POW_SRC}) 
set_target_properties (
	Otus_2 PROPERTIES 
	CXX_STANDARD 17 
	CXX_STANDARD_REQUIRED ON	
)

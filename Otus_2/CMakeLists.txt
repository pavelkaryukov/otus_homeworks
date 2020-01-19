cmake_minimum_required (VERSION 3.8)

project ("Otus_2" VERSION 0.0.1) 
set (ACM_TIMUS_SRC "acm_timus/acm_timus.cpp" "acm_timus/acm_timus.h")

add_executable(Otus_2 "otus_2.cpp" ${ACM_TIMUS_SRC}) 

set_target_properties (
	Otus_2 PROPERTIES 
	CXX_STANDARD 17 
	CXX_STANDARD_REQUIRED ON	
)

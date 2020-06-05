cmake_minimum_required (VERSION 3.8)

project ("Otus_15" VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER}) 

add_executable(kkmeans main.cpp ) 
set_target_properties (
	kkmeans 
	PROPERTIES 
	CXX_STANDARD 14
	CXX_STANDARD_REQUIRED ON	
)


find_package(dlib CONFIG REQUIRED)
if(NOT dlib_FOUND)
	message(SEND_ERROR "Failed to find dlib")
	return()
endif()   
Find_package(Threads)

message("\r\n\r\n${dlib_INCLUDE_DIRS}\r\n\r\n")
message("\r\n\r\n${dlib_LIBS}\r\n\r\n")
message("\r\n\r\n${dlib_LIBRARIES}\r\n\r\n")
target_include_directories(kkmeans PRIVATE  ${PROJECT_SOURCE_DIR} ${dlib_INCLUDE_DIRS} )
target_link_libraries(kkmeans 
    ${dlib_LIBS}      
    ${CMAKE_THREAD_LIBS_INIT}  
    $<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9.0>>:stdc++fs>
)

#IF (WIN32)
#    target_link_libraries(kkmeans 
#        ${dlib_LIBS}      
#        ${CMAKE_THREAD_LIBS_INIT}  
#        $<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9.0>>:stdc++fs>
#    )
#ELSE()
#    target_link_libraries(kkmeans 
#        dlib
#        blas
#        lapack
#        ${CMAKE_THREAD_LIBS_INIT}  
#        $<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9.0>>:stdc++fs>
#    )
#ENDIF()


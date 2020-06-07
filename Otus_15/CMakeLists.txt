cmake_minimum_required (VERSION 3.8)

project ("Otus_15" VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER}) 

add_executable(kkmeans main.cpp ) 
set_target_properties (
	kkmeans 
	PROPERTIES 
	CXX_STANDARD 14
	CXX_STANDARD_REQUIRED ON	
)



find_package(dlib REQUIRED) 
find_package(BLAS)
find_package(LAPACK)
Find_package(Threads)

#target_link_libraries(kkmeans 
#    ${dlib_LIBS}      
#    ${CMAKE_THREAD_LIBS_INIT}  
#    $<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9.0>>:stdc++fs>
#)
target_link_libraries(kkmeans 
    dlib     
    blas
    lapack
    ${CMAKE_THREAD_LIBS_INIT}  
    $<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9.0>>:stdc++fs>
)

#if(NOT dlib_FOUND)
#	message(SEND_ERROR "Failed to find dlib")
#	return()
#endif()  
message("\r\n\r\ndlib_INCLUDE_DIRS=${dlib_INCLUDE_DIRS}\r\n\r\n")
message("\r\n\r\ndlib_LIBS=${dlib_LIBS}\r\n\r\n")
message("\r\n\r\ndlib_LIBRARIES=${dlib_LIBRARIES}\r\n\r\n")
target_include_directories(kkmeans PRIVATE  ${PROJECT_SOURCE_DIR} ${dlib_INCLUDE_DIRS} )
#IF (WIN32)
#    target_link_libraries(kkmeans 
#        ${dlib_LIBS}      
#        ${CMAKE_THREAD_LIBS_INIT}  
#        $<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9.0>>:stdc++fs>
#    )
#ELSE()
#    target_link_libraries(kkmeans 
#        dlib::dlib
#        blas
#        lapack
#        ${CMAKE_THREAD_LIBS_INIT}  
#        $<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9.0>>:stdc++fs>
#    )
#ENDIF()


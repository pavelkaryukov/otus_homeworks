cmake_minimum_required (VERSION 3.8)

project ("Otus_15" VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER}) 

add_executable(kkmeans main.cpp ) 
add_executable(example example_main.cpp ) 
#add_executable(create_points create_points.cpp ) 
set_target_properties (
	kkmeans 
	example
#    create_points
	PROPERTIES 
	CXX_STANDARD 14
	CXX_STANDARD_REQUIRED ON	
)
 #использую для boost::format, boost::tokenizer
find_package(Boost REQUIRED)
if(NOT Boost_FOUND)
	message(SEND_ERROR "Failed to find boost")
	return()
endif()
find_package(BLAS)
find_package(Threads)

IF (WIN32)
	find_package(dlib)
	if(NOT dlib_FOUND)
		message(SEND_ERROR "Failed to find dlib")
		return()
	endif()  

	target_include_directories(kkmeans 
        PRIVATE  
            ${PROJECT_SOURCE_DIR} 
            ${dlib_INCLUDE_DIRS} 
            ${Boost_INCLUDE_DIRS}
    )
	target_link_libraries( kkmeans
	    ${dlib_LIBS}      
        ${CMAKE_THREAD_LIBS_INIT}  
        $<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9.0>>:stdc++fs>
    )
	
#    target_include_directories(create_points 
#        PRIVATE  
#            ${PROJECT_SOURCE_DIR} 
#            ${dlib_INCLUDE_DIRS} 
#            ${Boost_INCLUDE_DIRS}
#    )
#
#	target_link_libraries( create_points
#	    ${dlib_LIBS}      
#        ${CMAKE_THREAD_LIBS_INIT}  
#        ${Boost_LIBRARIES}
#        $<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9.0>>:stdc++fs>
#    )

    target_include_directories(example PRIVATE  ${PROJECT_SOURCE_DIR} ${dlib_INCLUDE_DIRS} )
    target_link_libraries( example	
        ${dlib_LIBS}      
        ${CMAKE_THREAD_LIBS_INIT}  
        $<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9.0>>:stdc++fs>
    )
ELSE()
    target_include_directories(kkmeans 
        PRIVATE  
            ${PROJECT_SOURCE_DIR} 
            ${dlib_INCLUDE_DIRS} 
            ${Boost_INCLUDE_DIRS}
    )
	target_link_libraries( kkmeans 
		dlib     
		blas
		lapack
		${CMAKE_THREAD_LIBS_INIT}  
		$<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9.0>>:stdc++fs>
	)
	target_link_libraries( example
		dlib     
		blas
		lapack
		${CMAKE_THREAD_LIBS_INIT}  
		$<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9.0>>:stdc++fs>
	)

#     target_include_directories(create_points 
#        PRIVATE  
#            ${PROJECT_SOURCE_DIR} 
#            ${Boost_INCLUDE_DIRS}
#    )
#
#	target_link_libraries( create_points
#		dlib     
#		blas
#		lapack
#        ${CMAKE_THREAD_LIBS_INIT}  
#        ${Boost_LIBRARIES}
#        $<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9.0>>:stdc++fs>
#    )	
ENDIF()


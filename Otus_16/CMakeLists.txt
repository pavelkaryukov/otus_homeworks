cmake_minimum_required (VERSION 3.8)

project ("Otus_16" VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER}) 

add_executable(rclst main_rclst.cpp ) 
add_executable(rclss main_rclss.cpp ) 


set_target_properties (
	rclst
    rclss 
	PROPERTIES 
	CXX_STANDARD 14
	CXX_STANDARD_REQUIRED ON	
)

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

	target_include_directories(rclst 
        PRIVATE  
            ${PROJECT_SOURCE_DIR} 
            ${dlib_INCLUDE_DIRS} 
            ${Boost_INCLUDE_DIRS}
    )

	target_link_libraries( rclst
	    ${dlib_LIBS}      
        ${CMAKE_THREAD_LIBS_INIT}  
        $<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9.0>>:stdc++fs>
    )

    target_include_directories(rclss 
        PRIVATE  
            ${PROJECT_SOURCE_DIR} 
            ${dlib_INCLUDE_DIRS} 
            ${Boost_INCLUDE_DIRS}
    )

	target_link_libraries(rclss
	    ${dlib_LIBS}      
        ${CMAKE_THREAD_LIBS_INIT}  
        $<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9.0>>:stdc++fs>
    )
ELSE()
	target_include_directories(rclst 
        PRIVATE  
            ${PROJECT_SOURCE_DIR} 
            ${Boost_INCLUDE_DIRS}
    )

	target_link_libraries( rclst
	    dlib     
		blas
		lapack    
        ${CMAKE_THREAD_LIBS_INIT}  
        $<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9.0>>:stdc++fs>
    )

    target_include_directories(rclss 
        PRIVATE  
            ${PROJECT_SOURCE_DIR} 
            ${Boost_INCLUDE_DIRS}
    )

	target_link_libraries(rclss
	    dlib     
		blas
		lapack     
        ${CMAKE_THREAD_LIBS_INIT}  
        $<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9.0>>:stdc++fs>
    )
ENDIF()

set (DATASET_FILE_PATH ${PROJECT_SOURCE_DIR}/16.dataset-12995-8e405d.csv)
file(COPY ${DATASET_FILE_PATH} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


####################################################
################_INSTALL_BLOCK_#####################
install(TARGETS 
    rclst
    rclss 
    DESTINATION bin
)
set(CPACK_PACKAGE_NAME "OtusHomeworks")
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_VENDOR "Karyukov")
set(CPACK_PACKAGE_CONTACT "pavelkaryukov@gmail.com")
include (CPack)


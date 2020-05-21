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

IF (WIN32)
	set(ASYNC_LIB_PATH ${PROJECT_SOURCE_DIR}/lib/libasync.lib)	
ELSE()
	set(ASYNC_LIB_PATH ${PROJECT_SOURCE_DIR}/lib/libasync.a)
ENDIF()

target_link_libraries(bulk_server
        ${Boost_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT}
		${ASYNC_LIB_PATH}# учитывать возможность a файла 
)

add_subdirectory ("client")

##############################################
###################INSTALL####################
install(TARGETS bulk_server  DESTINATION bin)	   
set(CPACK_PACKAGE_NAME "OtusHomeworks")
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_VENDOR "Karyukov")
set(CPACK_PACKAGE_CONTACT "pavelkaryukov@gmail.com")
include (CPack)
   

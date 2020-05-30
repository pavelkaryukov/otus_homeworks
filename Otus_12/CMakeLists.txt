cmake_minimum_required (VERSION 3.8)

project ("Otus_12" VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER}) 

set(CMD_SRC            "lib/dispatcher/command/icommand.h" 
                       "lib/dispatcher/command/simple_command.h")
set(LOG_SRC            "lib/dispatcher/logger/logger.h" 
                       "lib/dispatcher/logger/logger_screen.h" 
                       "lib/dispatcher/logger/logger_file.h")
set(CONCURRENT_SRC     "lib/dispatcher/concurrent/concurrent_deque.h")
set(DISPATCHER_SRC     "lib/dispatcher/dispatcher.h" ${CONCURRENT_SRC} ${LOG_SRC} ${CMD_SRC})   
#\dispatcher block

set(ASYNC_LIB_SRC "lib/bulk_async.h" "lib/bulk_async.cpp" ${DISPATCHER_SRC})



add_executable(bulk_server main.cpp ${ASYNC_LIB_SRC})
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
	${Boost_INCLUDE_DIR}
    ${PROJECT_SOURCE_DIR}/lib
    ${PROJECT_SOURCE_DIR}/lib/dispatcher
)


target_link_libraries(bulk_server
        ${Boost_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT}
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
   

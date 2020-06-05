cmake_minimum_required (VERSION 3.8.2)

project ("Otus_15" VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER}) 

add_executable(cat main.cpp ) 
set_target_properties (
	cat 
	PROPERTIES 
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON	
)

#SET(dlib_DIR "c:\\Program Files (x86)\\Project\\lib\\cmake\\dlib" )
find_package(dlib REQUIRED)
if(NOT dlib_FOUND)
	message(SEND_ERROR "Failed to find dlib")
	return()
endif()   

message("\r\n\r\n${dlib_INCLUDE_DIRS}\r\n\r\n")
message("\r\n\r\n${dlib_LIBS}\r\n\r\n")
message("\r\n\r\n${dlib_LIBRARIES}\r\n\r\n")
#message(SEND_ERROR "Failed to find dlib")
		
#set(dlib_LIBRARIES ${dlib_LIBRARIES} "ws2_32;winmm;comctl32;gdi32;imm32")
#set(dlib_LIBS      ${dlib_LIBRARIES} "ws2_32;winmm;comctl32;gdi32;imm32")
#set(dlib_INCLUDE_DIRS "C:/Program Files (x86)/Project/include" "")
target_include_directories(cat PRIVATE  ${dlib_INCLUDE_DIRS} )
target_link_libraries(cat ${dlib_LIBS} )
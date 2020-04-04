cmake_minimum_required (VERSION 3.8)

project ("Otus_5" VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER}) 

set(APP_SRC     "application/application.h")
set(FILES_SRC   "file_system/file_manager.h" "file_system/all_files.h" "file_system/files/ifile.h" 
				"file_system/files/file_jpg.h" "file_system/files/file_bmp.h" "file_system/files/file_vect.h")

set(SHAPES_SRC  "shape/ishape.h" "shape/circle.h" "shape/rectangle.h" "shape/line.h" "shape/utility/color.h" "shape/utility/coord.h")			
set(ERRORS_SRC  "error_code/my_error_code.h")	
set(WORK_SPACE_SRC    "work_space/canvas.h" "work_space/painter.h")

add_executable(graphic_editor otus_5.cpp ${APP_SRC} ${FILES_SRC} ${SHAPES_SRC} ${ERRORS_SRC} ${WORK_SPACE_SRC}) 

#Boost FMT
find_package(Boost REQUIRED)
if(NOT Boost_FOUND)
	message(SEND_ERROR "Failed to find boost")
	return()
endif()
set_target_properties (
	graphic_editor PROPERTIES 
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON	
)

target_link_libraries(graphic_editor PRIVATE $<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9.0>>:stdc++fs>)
target_include_directories(graphic_editor PRIVATE ${PROJECT_SOURCE_DIR}  ${Boost_INCLUDE_DIRS})

install(TARGETS graphic_editor DESTINATION bin)
set(CPACK_PACKAGE_NAME "OtusHomeworks")
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_VENDOR "Karyukov")
set(CPACK_PACKAGE_CONTACT "pavelkaryukov@gmail.com")
include (CPack)
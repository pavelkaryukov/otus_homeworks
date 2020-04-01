cmake_minimum_required (VERSION 3.8)

project ("Otus_2" VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER}) 

set(SHAPES_SRC  "shape/ishape.h" "shape/circle.h" "shape/rectangle.h" "shape/line.h" "shape/utility/color.h" "shape/utility/coord.h")			
set(ERRORS_SRC  "error_code/my_error_code.h")	
set(FILES_SRC   "file_system/file.h")
set(APP_SRC     "application/canvas.h" "application/painter.h")


add_executable(graphic_editor otus_5.cpp ${SHAPES_SRC}  ${ERRORS_SRC} ${FILES_SRC} ${APP_SRC})
set_target_properties (
	graphic_editor PROPERTIES 
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON	
)
cmake_minimum_required (VERSION 3.8)

project ("Otus_2" VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER}) 

set(SHAPE_FLDR  "shape")										   
add_executable(graphic_editor otus_5.cpp "shape/shape.h")
set_target_properties (
	graphic_editor PROPERTIES 
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON	
)
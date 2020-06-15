# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("Homeworks")

if (NOT DEFINED ENV{TRAVIS_BUILD_NUMBER})
	set(ENV{TRAVIS_BUILD_NUMBER} 1) # 
	message("Failed to find ENV TRAVIS_BUILD_NUMBER, set default value = 1")
endif()
# Include sub-projects.

add_subdirectory ("Otus_1")	
add_subdirectory ("Otus_2")
add_subdirectory ("Otus_3")	  
add_subdirectory ("Otus_4")
add_subdirectory ("Otus_5")
add_subdirectory ("Otus_6")
add_subdirectory ("Otus_7")
add_subdirectory ("Otus_8")
add_subdirectory ("Otus_9")	 
add_subdirectory ("Otus_10")
add_subdirectory ("Otus_11")	  
add_subdirectory ("Otus_12") 	  
add_subdirectory ("Otus_13")
add_subdirectory ("Otus_14")
add_subdirectory ("Otus_15")
add_subdirectory ("Otus_16")


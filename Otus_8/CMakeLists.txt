cmake_minimum_required (VERSION 3.8)

project ("Otus_8" VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER}) 

add_executable(timus_1196 timus_1196.cpp)
add_executable(timus_1545 timus_1545.cpp)
add_executable(timus_1496 timus_1496.cpp)
add_executable(timus_1837 timus_1837.cpp)

set_target_properties (
	timus_1196
	timus_1545
	timus_1496
	timus_1837
	PROPERTIES 
	CXX_STANDARD 14 
	CXX_STANDARD_REQUIRED ON	
)
													
install(TARGETS timus_1196 timus_1545 timus_1496 timus_1837 DESTINATION bin)
set(CPACK_PACKAGE_NAME "OtusHomeworks")
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_VENDOR "Karyukov")
set(CPACK_PACKAGE_CONTACT "pavelkaryukov@gmail.com")
include (CPack)
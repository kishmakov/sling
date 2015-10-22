cmake_minimum_required(VERSION 2.8)
project(sling)                   

set(CMAKE_BUILD_TYPE "None")
set(CMAKE_C_FLAGS "-g -fPIC -std=c11 -Wall")

include_directories(${CMAKE_SOURCE_DIR}/include) 
include_directories(${CMAKE_SOURCE_DIR}/src) 
include_directories(${CMAKE_SOURCE_DIR}/test) 

link_directories(${CMAKE_SOURCE_DIR}/3rdparty)   

# TODO: fix inclusion of cmoka sources to the target sources
add_library(cmocka SHARED ${PROJECT_SOURCE_DIR}/3rdparty/cmocka.c)   
set_target_properties(cmocka PROPERTIES EXCLUDE_FROM_ALL TRUE)
set_target_properties(cmocka PROPERTIES COMPILE_FLAGS "-DCMOCKA_EXPORTS -DHAVE_CONFIG_H=1 -fstack-protector -D_GNU_SOURCE -D_LARGEFILE64_SOURCE") 

file(GLOB_RECURSE SLING_SRC ${PROJECT_SOURCE_DIR}/src *.c)
file(GLOB_RECURSE TESTS_SRC ${PROJECT_SOURCE_DIR}/test *.c)
add_executable(unit-tests ${TESTS_SRC} ${SLING_SRC})

target_link_libraries(unit-tests cmocka) 
add_test(unit-tests unit-tests)





# code level cmakelists
cmake_minimum_required (VERSION 2.8)
message("CMAKE LEVEL: CODE >>>>>>>>>>>>>>>>>>>>")

project(archmq)

set( LOTUS_INC     ${CMAKE_CURRENT_SOURCE_DIR}/deps/lotus/code/lotus/inc )

add_subdirectory( deps/lotus/code)
add_subdirectory( archmq )
add_subdirectory( archmq2 )

message("CMAKE LEVEL: CODE <<<<<<<<<<<<<<<<<<<<<")
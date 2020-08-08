# code level cmakelists
cmake_minimum_required (VERSION 3.0)
message("CMAKE LEVEL: CODE >>>>>>>>>>>>>>>>>>>>")

project(archmq)

set( LOTUS_INC     ${CMAKE_CURRENT_SOURCE_DIR}/deps/lotus/code/lotus/inc )
set( ARCHMQ2_INC   ${CMAKE_CURRENT_SOURCE_DIR}/archmq2/inc )

add_subdirectory( deps/lotus/code)
add_subdirectory( archmq )
add_subdirectory( archmq2 )
add_subdirectory( archmq2test )

message("CMAKE LEVEL: CODE <<<<<<<<<<<<<<<<<<<<<")
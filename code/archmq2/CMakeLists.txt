#archmq2 level cmakelists
cmake_minimum_required (VERSION 3.0)
message("CMAKE LEVEL: ARCHMQ2 >>>>>>>>>>>>>>>>>>>>")

set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}")

FILE(GLOB_RECURSE ARCHMQ2_INC_FILES "inc/*.hpp")
aux_source_directory (src ARCHMQ2_SRC_FILES)

include_directories( ${LOTUS_INC} )
include_directories( inc )

add_library( archmq2 SHARED
    ${ARCHMQ2_INC_FILES}
    ${ARCHMQ2_SRC_FILES}
)

target_link_libraries( archmq2
    lotus_a
)

message("CMAKE LEVEL: ARCHMQ2 <<<<<<<<<<<<<<<<<<<<<")


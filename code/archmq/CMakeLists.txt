#archmq level cmakelists
cmake_minimum_required (VERSION 3.0)
message("CMAKE LEVEL: ARCHMQ >>>>>>>>>>>>>>>>>>>>")

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}")

FILE(GLOB_RECURSE ARCHMQ_INC_FILES "inc/*.hpp")
aux_source_directory (src ARCHMQ_SRC_FILES)

include_directories( inc )
include_directories( ${LOTUS_INC} )

add_executable( archmq
    ${ARCHMQ_INC_FILES}
    ${ARCHMQ_SRC_FILES}
)

target_link_libraries( archmq
    lotus_a
)

message("CMAKE LEVEL: ARCHMQ <<<<<<<<<<<<<<<<<<<<<")


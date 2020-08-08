#archmq2test level cmakelists
cmake_minimum_required (VERSION 3.0)
message("CMAKE LEVEL: ARCHMQ2TEST >>>>>>>>>>>>>>>>>>>>")

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}")

FILE(GLOB_RECURSE ARCHMQ2TEST_INC_FILES "inc/*.hpp")
aux_source_directory (src ARCHMQ2TEST_SRC_FILES)

include_directories( ${LOTUS_INC} )
include_directories( ${ARCHMQ2_INC} )
include_directories( inc )

add_executable( archmq2test
    ${ARCHMQ2TEST_INC_FILES}
    ${ARCHMQ2TEST_SRC_FILES}
)

target_link_libraries( archmq2test
    archmq2
)

message("CMAKE LEVEL: ARCHMQ2TEST <<<<<<<<<<<<<<<<<<<<<")



#archmq2test level cmakelists
cmake_minimum_required (VERSION 3.0)
message("CMAKE LEVEL: ARCHMQTEST >>>>>>>>>>>>>>>>>>>>")

set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}")

FILE(GLOB_RECURSE ARCHMQTEST_INC_FILES "inc/*.hpp")
aux_source_directory (src ARCHMQTEST_SRC_FILES)

include_directories( inc )
include_directories( ${LOTUS_INC} )

add_executable( archmqtest
    ${ARCHMQTEST_INC_FILES}
    ${ARCHMQTEST_SRC_FILES}
)

target_link_libraries( archmqtest
    lotus_a
)

message("CMAKE LEVEL: ARCHMQTEST <<<<<<<<<<<<<<<<<<<<<")



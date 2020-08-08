#archmq2 level cmakelists
cmake_minimum_required (VERSION 2.8)
message("CMAKE LEVEL: ARCHMQ2 >>>>>>>>>>>>>>>>>>>>")

FILE(GLOB_RECURSE ARCHMQ2_INC_FILES "inc/*.hpp")
aux_source_directory (src ARCHMQ2_SRC_FILES)

include_directories( inc )
include_directories( ${LOTUS_INC} )

add_library( archmq2_a STATIC
    ${ARCHMQ2_INC_FILES}
    ${ARCHMQ2_SRC_FILES}
)

target_link_libraries( archmq2_a
    lotus_a
)

message("CMAKE LEVEL: ARCHMQ2 <<<<<<<<<<<<<<<<<<<<<")


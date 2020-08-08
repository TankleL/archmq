#archmq2test level cmakelists
cmake_minimum_required (VERSION 2.8)
message("CMAKE LEVEL: ARCHMQ2TEST >>>>>>>>>>>>>>>>>>>>")

FILE(GLOB_RECURSE ARCHMQ2TEST_INC_FILES "inc/*.hpp")
aux_source_directory (src ARCHMQ2TEST_SRC_FILES)

include_directories( inc )
include_directories( ${LOTUS_INC} )
include_directories( ${ARCHMQ2_INC} )


add_executable( archmq2test
    ${ARCHMQ2TEST_INC_FILES}
    ${ARCHMQ2TEST_SRC_FILES}
)

target_link_libraries( archmq2test
    archmq2_a
)

message("CMAKE LEVEL: ARCHMQ2TEST <<<<<<<<<<<<<<<<<<<<<")



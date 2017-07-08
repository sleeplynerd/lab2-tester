project( tests )
add_subdirectory( gtest )

include_directories( ${PROJECT_BINARY_DIR}/../src )
include_directories( ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} )

add_executable( tests main.cpp )
target_link_libraries( tests src )
target_link_libraries( tests gtest gtest_main )
#

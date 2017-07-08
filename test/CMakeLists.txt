project( tests )
add_definitions( -D_VARIADIC_MAX=10 )
add_definitions( -D_DEBUG )
add_definitions( -D_MT )
add_definitions( -D_DLL )
add_subdirectory( gtest )

include_directories( ${PROJECT_BINARY_DIR}/../src )
include_directories( ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} )

add_executable( tests main.cpp )
target_link_libraries( tests src )
target_link_libraries( tests gtest gtest_main )
#

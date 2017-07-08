project( src )

set( STG_LIST_DIR ${PROJECT_SOURCE_DIR}/../variants_descriptions )
set( STG_LIST_PFX VARIANT_)


#		------------ VARIANT 1 ------------
if( EXISTS ${PROJECT_SOURCE_DIR}/../VARIANTS/VARIANT_1.cpp )
	set( VARIANT_1 ON )
endif()

#		------------ VARIANT 2 ------------
if( EXISTS ${PROJECT_SOURCE_DIR}/../VARIANTS/VARIANT_2.cpp )
	set( VARIANT_2 ON )
endif()

#		------------ VARIANT 3 ------------
if( EXISTS ${PROJECT_SOURCE_DIR}/../VARIANTS/VARIANT_3.cpp )
	set( VARIANT_3 ON )
endif()

#		------------ VARIANT 4 ------------
if( EXISTS ${PROJECT_SOURCE_DIR}/../VARIANTS/VARIANT_4.cpp )
	set( VARIANT_4 ON )
endif()

#		------------ VARIANT 5 ------------
if( EXISTS ${PROJECT_SOURCE_DIR}/../VARIANTS/VARIANT_5.cpp )
	set( VARIANT_5 ON )
endif()

#		------------ VARIANT 6 ------------
if( EXISTS ${PROJECT_SOURCE_DIR}/../VARIANTS/VARIANT_6.cpp )
	set( VARIANT_6 ON )
endif()

#		------------ VARIANT 7 ------------
if( EXISTS ${PROJECT_SOURCE_DIR}/../VARIANTS/VARIANT_7.cpp )
	set( VARIANT_7 ON )
endif()

#		------------ VARIANT 8 ------------
if( EXISTS ${PROJECT_SOURCE_DIR}/../VARIANTS/VARIANT_8.cpp )
	set( VARIANT_8 ON )
endif()

#		------------ VARIANT 9 ------------
if( EXISTS ${PROJECT_SOURCE_DIR}/../VARIANTS/VARIANT_9.cpp )
	set( VARIANT_9 ON )
endif()

#		------------ VARIANT 10 ------------
if( EXISTS ${PROJECT_SOURCE_DIR}/../VARIANTS/VARIANT_10.cpp )
	set( VARIANT_10 ON )
endif()

#		------------ VARIANT 11 ------------
if( EXISTS ${PROJECT_SOURCE_DIR}/../VARIANTS/VARIANT_11.cpp )
	set( VARIANT_11 ON )
endif()

#		------------ VARIANT 12 ------------
if( EXISTS ${PROJECT_SOURCE_DIR}/../VARIANTS/VARIANT_12.cpp )
	set( VARIANT_12 ON )
endif()

#		------------ VARIANT 13 ------------
if( EXISTS ${PROJECT_SOURCE_DIR}/../VARIANTS/VARIANT_13.cpp )
	set( VARIANT_13 ON )
endif()

#		------------ VARIANT 14 ------------
if( EXISTS ${PROJECT_SOURCE_DIR}/../VARIANTS/VARIANT_14.cpp )
	set( VARIANT_14 ON )
endif()

#		------------ VARIANT 15 ------------
if( EXISTS ${PROJECT_SOURCE_DIR}/../VARIANTS/VARIANT_15.cpp )
	set( VARIANT_15 ON )
endif()

#		------------ VARIANT 16 ------------
if( EXISTS ${PROJECT_SOURCE_DIR}/../VARIANTS/VARIANT_16.cpp )
	set( VARIANT_16 ON )
endif()

#		------------ VARIANT 17 ------------
if( EXISTS ${PROJECT_SOURCE_DIR}/../VARIANTS/VARIANT_17.cpp )
	set( VARIANT_17 ON )
endif()

#		------------ VARIANT 18 ------------
if( EXISTS ${PROJECT_SOURCE_DIR}/../VARIANTS/VARIANT_18.cpp )
	set( VARIANT_18 ON )
endif()

#		------------ VARIANT 19 ------------
if( EXISTS ${PROJECT_SOURCE_DIR}/../VARIANTS/VARIANT_19.cpp )
	set( VARIANT_19 ON )
endif()

#		------------ VARIANT 20 ------------
if( EXISTS ${PROJECT_SOURCE_DIR}/../VARIANTS/VARIANT_20.cpp )
	set( VARIANT_20 ON )
endif()



configure_file(
    variant.h.in
	variant.h)

#include_directories( ${PROJECT_SOURCE_DIR} )
include_directories( ${PROJECT_BINARY_DIR} )
file( GLOB_RECURSE SOURCE_VARIANTS "${PROJECT_SOURCE_DIR}/../VARIANTS/*.cpp" )
add_library( src variant.cpp variant.h )
#if( EXISTS ${SOURCE_VARIANTS} )
if( SOURCE_VARIANTS )
	#message( "src: All the files has been found" )
	target_link_libraries( src VARIANTS )
#else()
#	message( "src: No files was found")
endif()

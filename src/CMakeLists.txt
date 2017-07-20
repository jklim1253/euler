cmake_minimum_required ( VERSION 3.0 )

set ( SRC_FILES
    main.cpp
    )

set ( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
set ( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/lib )
set ( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/lib )

configure_file (
    "${CMAKE_SOURCE_DIR}/src/config/define.h.in"
    "${CMAKE_BINARY_DIR}/src/inc/define.h"
    )

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_BINARY_DIR}/src)

set ( OUTPUT_FILE
    "${CMAKE_PROJECT_NAME}-${VERSION_MAJOR}.${VERSION_MINOR}${BUILD_TYPE_SUFFIX}"
    )

add_subdirectory(030)

add_executable ( ${CMAKE_PROJECT_NAME} ${SRC_FILES} )
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES OUTPUT_NAME ${OUTPUT_FILE})
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "d")


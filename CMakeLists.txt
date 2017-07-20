cmake_minimum_required ( VERSION 3.0.2 )
project ( euler-solution )

set ( VERSION_MAJOR 1 )
set ( VERSION_MINOR 0 )

#set (CMAKE_BUILD_TYPE Debug)

# append module path to use custom module.
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

# prevent to build on root directory.
include (prevent_root_build)

add_subdirectory(src)

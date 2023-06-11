cmake_minimum_required (VERSION 3.10)

################################################################################
# Project definition
################################################################################

project(tetris
        VERSION 0.0.1
        LANGUAGES CXX)

################################################################################
# Init cmake modules path
################################################################################

set(COMMON_CMAKE_DIR cmake)
set(COMMON_MAIN_CMAKE ${COMMON_CMAKE_DIR}/main.cmake)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/${COMMON_CMAKE_DIR} ${CMAKE_MODULE_PATH})

include(${COMMON_MAIN_CMAKE} PUBLIC)

################################################################################
# Include source code
################################################################################

include(find_packages.cmake PUBLIC)

add_subdirectory(externals)
add_subdirectory(libs/core)
add_subdirectory(src/console)
add_subdirectory(tests)


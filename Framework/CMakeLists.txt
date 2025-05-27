cmake_minimum_required(VERSION 3.29)
project(Framework)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(
        ${INCLUDE_DIR}
        ${SOURCE_DIR}
        ${VENDOR_DIR}/glfw/include
)

file(GLOB_RECURSE API_INCLUDE_LIST
        "${INCLUDE_DIR}/*.h"
        "${INCLUDE_DIR}/*.hpp"
)

file(GLOB_RECURSE INCLUDE_LIST
        "${SOURCE_DIR}/*.h"
        "${SOURCE_DIR}/*.hpp"
)

file(GLOB_RECURSE SOURCE_LIST
        "${SOURCE_DIR}/*.cpp"
)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
add_subdirectory("${VENDOR_DIR}/glfw" "${VENDOR_DIR}/glfw/build")

add_library(Framework STATIC
        ${API_INCLUDE_LIST}
        ${INCLUDE_LIST}
        ${SOURCE_LIST}
)
target_link_libraries(Framework PUBLIC glfw)
target_link_libraries(Framework PUBLIC opengl32.lib)

set_target_properties(
        Framework
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Output/Framework/${CMAKE_BUILD_TYPE}
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Output/Framework/${CMAKE_BUILD_TYPE}
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Output/Framework/${CMAKE_BUILD_TYPE}
)

set_target_properties(Framework PROPERTIES OUTPUT_NAME "Saturn2D")
target_precompile_headers(Framework PUBLIC "${SOURCE_DIR}/Precompiled.hpp")
cmake_minimum_required(VERSION 3.29)
project(Framework)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)



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
add_subdirectory("${VENDOR_DIR}/glfw" "${CMAKE_CURRENT_BINARY_DIR}/glfw")
set(SPDLOG_HEADER_ONLY OFF CACHE BOOL "" FORCE)
add_subdirectory("${VENDOR_DIR}/spdlog" "${CMAKE_CURRENT_BINARY_DIR}/spdlog")
add_subdirectory("${VENDOR_DIR}/glad" "${CMAKE_CURRENT_BINARY_DIR}/glad")

add_library(Framework STATIC
        ${API_INCLUDE_LIST}
        ${INCLUDE_LIST}
        ${SOURCE_LIST}
)

target_include_directories(
        Framework
        PUBLIC
        ${INCLUDE_DIR}
        ${VENDOR_DIR}/glm
)

target_link_libraries(Framework PUBLIC glfw)
target_link_libraries(Framework PUBLIC spdlog::spdlog)
target_link_libraries(Framework PUBLIC glad)

target_compile_definitions(
        Framework
        PUBLIC
        $<$<CONFIG:Debug>:DEBUG_BUILD>
)

if(SATURN_DEFINE_MAIN)
    target_compile_definitions(
            Framework
            PUBLIC
            SATURN_FX_MAIN
    )
endif()

target_include_directories(
        Framework
        PRIVATE
        ${SOURCE_DIR}
)

set_target_properties(
        Framework
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Output/Framework/${CMAKE_BUILD_TYPE}
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Output/Framework/${CMAKE_BUILD_TYPE}
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Output/Framework/${CMAKE_BUILD_TYPE}
)

set_target_properties(Framework PROPERTIES OUTPUT_NAME "SaturnFX")
target_precompile_headers(Framework PUBLIC "${SOURCE_DIR}/Precompiled.hpp")
cmake_minimum_required(VERSION 3.16)
project(glad)

add_library(glad STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/gl.c
)

target_include_directories(glad INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
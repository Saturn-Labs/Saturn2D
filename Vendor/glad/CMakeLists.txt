cmake_minimum_required(VERSION 3.16)
project(glad)

add_library(glad INTERFACE)
target_include_directories(glad INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
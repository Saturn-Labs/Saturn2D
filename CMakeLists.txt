cmake_minimum_required(VERSION 3.29)
project(Saturn2D)
set(CMAKE_CXX_STANDARD 20)
set(SOURCE_DIR "Source")
set(INCLUDE_DIR "Include")
set(VENDOR_DIR "${CMAKE_CURRENT_LIST_DIR}/Vendor")

add_subdirectory(Framework)
add_subdirectory(Application)
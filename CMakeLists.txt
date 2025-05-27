cmake_minimum_required(VERSION 3.29)
project(Saturn2D)
set(CMAKE_CXX_STANDARD 20)
set(SOURCE_DIR "source")
set(INCLUDE_DIR "include")
set(VENDOR_DIR "vendor")

add_subdirectory(Framework)
add_subdirectory(Application)
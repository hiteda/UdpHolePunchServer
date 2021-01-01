cmake_minimum_required(VERSION 3.10)

project(UdpHolePunchServer VERSION 1.0)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
message ("CXX Flags: " ${CMAKE_CXX_FLAGS})

add_subdirectory(src)
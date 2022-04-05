cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project("XSystem")

include(CMake/XSystem.cmake)

add_subdirectory("SDK")
add_subdirectory("Kernel")
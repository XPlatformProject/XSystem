cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(XSystem.Kernel)

add_library(XSystem.Kernel SHARED "src/general.h" "src/main.cpp" "src/kernel/kernel.cpp" "src/ini_parser/ini_parser.cpp" "src/ini_parser/api/ini_parser_api.cpp")

add_library(XSystem.Kernel-headers INTERFACE)
target_include_directories(XSystem.Kernel-headers INTERFACE "include/")

set_property(TARGET XSystem.Kernel PROPERTY POSITION_INDEPENDENT_CODE ON)

target_link_libraries(XSystem.Kernel PRIVATE XSystem.SDK XSystem.Kernel-headers)
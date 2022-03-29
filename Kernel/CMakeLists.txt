cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project("XSystem")

add_library(XSystem.kernel SHARED "src/main.cpp" "src/kernel/kernel.h" "src/kernel/kernel.cpp" "src/ini_parser/ini_parser.h" "src/ini_parser/ini_parser.cpp" "src/general.h" "include/XSystem.kernel/ini.h" "src/ini_parser/api/ini_parser_api.h" "src/ini_parser/api/ini_parser_api.cpp")

add_library(XSystem.kernel-headers INTERFACE)
target_include_directories(XSystem.kernel-headers INTERFACE "include/")

target_link_libraries(XSystem.kernel PRIVATE XSystem.SDK XSystem.kernel-headers)
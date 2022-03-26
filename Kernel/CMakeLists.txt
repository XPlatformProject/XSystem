cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project("XSystem")

add_library(XSystem.kernel SHARED "src/main.cpp" "src/kernel/kernel.h" "src/kernel/kernel.cpp" "src/ini_parser/ini_parser.h" "src/ini_parser/ini_parser.cpp" "src/general.h")

target_link_libraries(XSystem.kernel PRIVATE XSystem.SDK)
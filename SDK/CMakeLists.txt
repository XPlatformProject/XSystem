cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project("XSystem")

add_library(XSystem.SDK STATIC "include/XSystem/XSystem.h" "src/main.cpp"  "src/Loader/Loader.cpp" "src/general.h" "include/XSystem/Loader.h")

target_include_directories(XSystem.SDK PUBLIC "include/")
cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project("XSystem")

add_library(XSystem.SDK STATIC "src/main.cpp" "src/general.h" "src/Loader/Loader.cpp")
target_include_directories(XSystem.SDK PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

message(${CMAKE_CURRENT_SOURCE_DIR})

if(UNIX)
target_compile_options(XSystem.SDK PRIVATE -fpic)
target_link_libraries(XSystem.SDK ${CMAKE_DL_LIBS})
endif(UNIX)
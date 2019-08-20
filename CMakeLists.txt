cmake_minimum_required(VERSION 3.8)

set(This Utf8)

project(${This} CXX)

set(CMAKE_CXX_STANDARD 11)

set(Headers
    include/utf8/Utf8.hpp
)

set (Sources
    src/Utf8.cpp
)

add_library(${This} STATIC ${Sources} ${Headers})
set_target_properties(${This} PROPERTIES
    FOLDER Libraries
)

target_include_directories(${This} PUBLIC include)

add_subdirectory(test)

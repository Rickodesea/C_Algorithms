cmake_minimum_required(VERSION 3.14)

project(CALGO VERSION 0.1.0 DESCRIPTION "General Purpose Cmake Scripts" LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

add_compile_definitions($<$<CONFIG:Debug>:DEBUG>)
add_compile_definitions($<$<CONFIG:Release>:NDEBUG>)

include_directories(Source)

add_executable(dynamic_array
    Source/dynamic_array/dynamic_array.c
    Source/dynamic_array/main.c
)

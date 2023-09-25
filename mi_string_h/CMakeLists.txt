cmake_minimum_required(VERSION 3.26)
project(mi_string_h C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(mi_string_h
        main.c
        mi_string_h.c
        mi_string_h.h)

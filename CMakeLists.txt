cmake_minimum_required(VERSION 3.20)
project(PP_C C)

set(CMAKE_C_STANDARD 11)

add_executable(PP_C main.c login.c book_management.c utility_functions.c
        library.h
)

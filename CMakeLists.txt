cmake_minimum_required(VERSION 3.12)
project(C_Calculator C)

set(CMAKE_C_STANDARD 11)

SET(CMAKE_EXE_LINKER_FLAGS "-lreadline")

add_executable(C_Calculator main.c solve.c solve.h resize.c resize.h io.c io.h)
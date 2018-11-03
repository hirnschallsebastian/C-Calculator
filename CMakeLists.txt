cmake_minimum_required(VERSION 3.9)
project(ccalc)

set(CMAKE_C_STANDARD 11)

SET(GCC_COVERAGE_LINK_FLAGS "-lreadline -lm")
SET(GCC_COVERAGE_COMPILE_FLAGS "-lreadline -lm")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")


add_executable(ccalc main.c solve.c solve.h resize.c resize.h io.c io.h plot.c plot.h)
target_link_libraries(ccalc readline)
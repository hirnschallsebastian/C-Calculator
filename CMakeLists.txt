cmake_minimum_required(VERSION 3.9)
project(C_Calculator)

set(CMAKE_C_STANDARD 11)

SET(GCC_COVERAGE_LINK_FLAGS "-lreadline")
SET(GCC_COVERAGE_COMPILE_FLAGS "-lreadline")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")


add_executable(C_Calculator main.c solve.c solve.h resize.c resize.h io.c io.h)
target_link_libraries(C_Calculator readline)
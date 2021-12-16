cmake_minimum_required(VERSION 3.22)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)  # Make clang-tidy happy

project(aoc-day02)
find_package(verilator HINTS $ENV{VERILATOR_ROOT})

add_executable(day02 sim.cpp)

verilate(day02 SOURCES day02.v TOP_MODULE partTwo TRACE)

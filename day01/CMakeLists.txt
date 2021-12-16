cmake_minimum_required(VERSION 3.22)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)  # Make clang-tidy happy

project(aoc-day01)
find_package(verilator HINTS $ENV{VERILATOR_ROOT})

add_executable(day01 sim.cpp)

verilate(day01 SOURCES verilog.v TOP_MODULE partTwo TRACE)


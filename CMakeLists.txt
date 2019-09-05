cmake_minimum_required(VERSION 3.14)
project(tp1_sudoku C)

set(CMAKE_C_STANDARD 99)

add_executable(tp1_sudoku src/main.c src/errors.c src/errors.h src/types.h src/main.h)
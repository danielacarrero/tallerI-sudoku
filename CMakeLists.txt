cmake_minimum_required(VERSION 3.14)
project(tp1_sudoku C)

set(CMAKE_C_STANDARD 99)

add_executable(tp1_sudoku src/main.c src/errors.c src/errors.h src/types.h src/main.h src/adt_socket.h src/adt_socket.c src/client.h src/client.c src/server.h src/server.c src/adt_sudoku.c src/adt_sudoku.h src/utils.h src/utils.c src/adt_vector.h src/adt_vector.c)
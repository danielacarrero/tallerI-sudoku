#ifndef TYPES__H
#define TYPES__H

#include <stdio.h>

#define MSG_OK "OK\n"
#define MSG_ERROR "ERROR\n"

typedef enum {
    ERROR_PROGRAM_INVOCATION,
    ERROR_SERVER_PROGRAM_INVOCATION,
    ERROR_CLIENT_PROGRAM_INVOCATION,
    ERROR_SOCKET_CONNECTION,
    ERROR_SOCKET_BINDING_AND_LISTEN,
    ERROR_ACCEPTING_SOCKET_CONNECTION,
    ERROR_CLOSED_SOCKET,
    ERROR_SOCKET_SENDING,
    ERROR_SOCKET_RECEIVING,
    ERROR_CREATING_SUDOKU,
    ERROR_FORMATTING_SUDOKU,
    ERROR_OPENING_FILE,
    ERROR_UNMODIFIABLE_CELL,
    ERROR_UNSUPPORTED_INDICES,
    ERROR_UNSUPPORTED_VALUE,
    ERROR_INVALID_DATA,
    ERROR_NULL_POINTER,
    ERROR_OUT_OF_MEMORY,
    ERROR_NOT_FOUND,
    OK
} status_t;

typedef enum {
    CLIENT,
    SERVER
} socket_type_t;

typedef status_t (*destructor_t)(void **);

#endif

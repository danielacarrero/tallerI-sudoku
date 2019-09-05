#ifndef TYPES__H
#define TYPES__H

#include <stdio.h>

typedef enum {
    ERROR_PROGRAM_INVOCATION,
    ERROR_SERVER_PROGRAM_INVOCATION,
    ERROR_CLIENT_PROGRAM_INVOCATION,
    ERROR_INVALID_DATA,
    ERROR_NULL_POINTER,
    OK
} status_t;

typedef enum {
    CLIENT,
    SERVER
} socket_type_t;

#endif

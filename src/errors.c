#include <stdio.h>
#include "errors.h"

char* errors [MAX_ERRORS] = {
        MSG_ERROR_PROGRAM_INVOCATION,
        MSG_ERROR_SERVER_PROGRAM_INVOCATION,
        MSG_ERROR_CLIENT_PROGRAM_INVOCATION,
        MSG_ERROR_SOCKET_CONNECTION,
        MSG_ERROR_SOCKET_BINDING_AND_LISTEN,
        MSG_ERROR_ACCEPTING_SOCKET_CONNECTION,
        MSG_ERROR_CLOSED_SOCKET,
        MSG_ERROR_SOCKET_SENDING,
        MSG_ERROR_SOCKET_RECEIVING
};

status_t print_error_msg(status_t code) {
    if(code >= MAX_ERRORS)
        return ERROR_INVALID_DATA;
    //perror(errors[code]);
    fprintf(stderr, "%s", errors[code]);
    return OK;
}

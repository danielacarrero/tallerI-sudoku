#include <stdio.h>
#include "errors.h"

char* errors [MAX_ERRORS] = {
        MSG_ERROR_PROGRAM_INVOCATION,
        MSG_ERROR_SERVER_PROGRAM_INVOCATION,
        MSG_ERROR_CLIENT_PROGRAM_INVOCATION
};

status_t print_error_msg(status_t code) {
    if(code >= MAX_ERRORS)
        return ERROR_INVALID_DATA;
    fprintf(stderr, "%s\n", errors[code]);
    return OK;
}

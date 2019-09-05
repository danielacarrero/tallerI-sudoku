#include <stdio.h>
#include <string.h>
#include "main.h"

int main(int argc, char *argv[]) {
    status_t st;

    if((st = validate_arguments(argc, argv)) != OK) {
        print_error_msg(st);
        return ERROR;
    }

    return SUCCESSFUL;
}

status_t validate_arguments(int argc, char *argv[]) {

    if(argv == NULL) {
        return ERROR_NULL_POINTER;
    }

    if(argc < CMD_ARG_MINIMUM_NUMBER) {
        return ERROR_PROGRAM_INVOCATION;
    }

    if(!strcmp(argv[CMD_ARG_SOCKET_TYPE_POSITION], CMD_ARG_SERVER_TYPE)) {
        if(argc < CMD_ARG_SERVER_NUMBER) {
            return ERROR_SERVER_PROGRAM_INVOCATION;
        }
    }

    if(!strcmp(argv[CMD_ARG_SOCKET_TYPE_POSITION], CMD_ARG_CLIENT_TYPE)) {
        if(argc < CMD_ARG_CLIENT_NUMBER) {
            return ERROR_CLIENT_PROGRAM_INVOCATION;
        }
    }

    return OK;
}

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "main.h"

int main(int argc, char *argv[]) {
    status_t st;

    if ((st = validate_arguments(argc, argv)) != OK) {
        print_error_msg(st);
        return ERROR;
    }

    if (is_client(argv)) {
        char *host = argv[CMD_ARG_CLIENT_HOST_POSITION];
        char *service = argv[CMD_ARG_CLIENT_PORT_POSITION];
        if ((st = init_client(host, service)) != OK) {
            print_error_msg(st);
            return ERROR;
        }
    }

    if (is_server(argv)) {
        char *service = argv[CMD_ARG_SERVER_PORT_POSITION];
        if ((st = init_server(service)) != OK) {
            if (st == ERROR_CLOSED_SOCKET) {
                return SUCCESSFUL;
            } else {
                print_error_msg(st);
                return ERROR;
            }
        }
    }


    return SUCCESSFUL;
}

status_t validate_arguments(int argc, char *argv[]) {
    if (argv == NULL) {
        return ERROR_NULL_POINTER;
    }

    if (argc < CMD_ARG_MINIMUM_NUMBER) {
        return ERROR_PROGRAM_INVOCATION;
    }

    if (is_server(argv)) {
        if (argc < CMD_ARG_SERVER_NUMBER) {
            return ERROR_SERVER_PROGRAM_INVOCATION;
        }
    }

    if (is_client(argv)) {
        if (argc < CMD_ARG_CLIENT_NUMBER) {
            return ERROR_CLIENT_PROGRAM_INVOCATION;
        }
    }

    return OK;
}

bool is_client(char *argv[]) {
    return (!strcmp(argv[CMD_ARG_SOCKET_TYPE_POSITION], CMD_ARG_CLIENT_TYPE));
}

bool is_server(char *argv[]) {
    return (!strcmp(argv[CMD_ARG_SOCKET_TYPE_POSITION], CMD_ARG_SERVER_TYPE));
}

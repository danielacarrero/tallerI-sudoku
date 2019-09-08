#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "server.h"


status_t init_server(const char *service) {
    socket_t socket;
    status_t st;

    socket.host = NULL;
    socket.service = service;

    if ((st = ADT_socket_init(&socket, SERVER)) != OK) {
        return st;
    }

    if ((st = ADT_socket_bind_and_listen(&socket)) != OK) {
        return st;
    }

    fprintf(stdout, "%s\n", "Server inicializado! :)");

    if ((st = wait_and_receive(&socket)) != OK) {
        ADT_socket_destroy(&socket);
        return st;
    }

    if ((st = ADT_socket_destroy(&socket)) != OK) {
        return st;
    }

    return OK;
}

status_t wait_and_receive(socket_t *socket) {
    status_t st = OK;
    int peer_fd = 0;
    int res = 0;
    char buffer[MAX_LENGTH_RECEIVED];

    memset(buffer, 0, MAX_LENGTH_RECEIVED);

    if ((st = ADT_socket_accept(socket, &peer_fd)) != OK) {
        return st;
    }

    while ((st = ADT_socket_receive(socket, peer_fd, &res, buffer, MAX_LENGTH_RECEIVED)) != ERROR_CLOSED_SOCKET) {
        if (res != MAX_LENGTH_RECEIVED) {
            buffer[res + 1] = '\0';
        }
        printf("buffer size: %d\n", res);
        printf("comando: %s\n", buffer);

        if((st = process_command_received(buffer)) != OK){
            print_error_msg(st);
        }

        memset(&buffer, 0, MAX_LENGTH_RECEIVED);
    }

    return st;
}

status_t process_command_received(const char *buffer) {
    switch(buffer[0]) {
        case CMD_GET:
            return process_get_command();
        case CMD_PUT:
            return process_put_command(buffer);
        case CMD_RESET:
            return process_reset_command();
        case CMD_VERIFY:
            return process_verify_command();
        default:
            return ERROR_INVALID_DATA;
    }
}

status_t process_get_command() {
    printf("Processing GET command\n");
    return OK;
}

status_t process_put_command(const char *buffer) {
    printf("Processing PUT command\n");
    return OK;
}

status_t process_reset_command() {
    printf("Processing RESET command\n");
    return OK;
}

status_t process_verify_command() {
    printf("Processing VERIFY command\n");
    return OK;
}

#include <stdio.h>
#include "server.h"


status_t init_server(const char *service) {
    socket_t socket;
    status_t st;

    socket.host = NULL;
    socket.service = service;

    if ((st = ADT_socket_init(&socket, SERVER)) != OK) {
        return st;
    }

    fprintf(stdout, "%s\n", "Server inicializado! :)");

    if ((st = ADT_socket_bind_and_listen(&socket)) != OK) {
        return st;
    }

    if ((st = ADT_socket_accept(&socket)) != OK) {
        return st;
    }

    if ((st = ADT_socket_receive(&socket, socket.buffer, MAX_LENGTH_RECEIVED)) != OK) {
        return st;
    }

    if ((st = ADT_socket_destroy(&socket)) != OK) {
        return st;
    }

    return OK;
}

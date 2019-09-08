#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "client.h"

status_t init_client(const char *host, const char *service) {
    socket_t socket;
    status_t st;

    socket.host = host;
    socket.service = service;

    if ((st = ADT_socket_init(&socket, CLIENT)) != OK) {
        return st;
    }

    if ((st = ADT_socket_connect(&socket)) != OK) {
        return st;
    }

    process_input(&socket);

    if ((st = ADT_socket_destroy(&socket)) != OK) {
        return st;
    }

    return OK;
}

void process_input(socket_t *socket) {
    fprintf(stderr, "%s\n", "Process user input!! ");
    char buf[CMD_MAX_INPUT_SIZE];
    bool exit = false;

    while(!exit){
        if(fgets(buf, CMD_MAX_INPUT_SIZE, stdin) == NULL){
            fprintf(stderr, "%s\n", "Error al leer de consola.");
            return;
        }

        if(!strncmp(CMD_EXIT, buf, strlen(CMD_EXIT))){
            exit = true;
        }

        ADT_socket_send(socket, buf, strlen(buf));
    }

    fprintf(stdout, "%s\n", buf);
}

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
    status_t st;
    fprintf(stderr, "%s\n", "Process user input!! ");
    char buf[CMD_MAX_INPUT_SIZE];
    bool exit = false;

    while(!exit){
        if(fgets(buf, CMD_MAX_INPUT_SIZE, stdin) == NULL){
            return;
        }

        if(!strncmp(CLIENT_CMD_EXIT, buf, strlen(CLIENT_CMD_EXIT))){
            exit = true;
        }

        if ((st = process_command(socket, buf)) != OK)
            print_error_msg(st);

        /*if((st = ADT_socket_send(socket, buf, strlen(buf))) != OK) {
            print_error_msg(st);
        }*/
    }

    fprintf(stdout, "%s\n", buf);
}

status_t process_command(socket_t *socket, char *buf) {
    if(!strncmp(CLIENT_CMD_GET, buf, strlen(CLIENT_CMD_GET))){
        return process_get(socket);
    }
    return ERROR_INVALID_DATA;
}

status_t process_get(socket_t *socket) {
    status_t st;

    if((st = ADT_socket_send(socket, SERVER_CMD_GET, sizeof(SERVER_CMD_GET))) != OK)
        return st;

    if((st = receive(socket)) != OK)
        return st;

    return OK;
}

status_t receive(socket_t *socket) {
    status_t st = OK;
    int peer_fd = 0;
    int res = 0;
    char buffer[MAX_SMALL_BUF_LEN];
    int next_len;
    int next_res = 0;


    if ((st = ADT_socket_bind_and_listen(socket)) != OK)
        return st;
    if ((st = ADT_socket_accept(socket, &peer_fd)) != OK)
        return st;

    if((st = ADT_socket_receive(socket, peer_fd, &res, buffer, MAX_SMALL_BUF_LEN)) == OK) {
        if (res != MAX_SMALL_BUF_LEN) {
            buffer[res + 1] = '\0';
        }

        next_len = ntohs((int) buffer);
        char next_buffer[next_len];

        if ((st = ADT_socket_receive(socket, peer_fd, &next_res, next_buffer, next_len)) != OK) {
            return st;
        }

        printf("%s", next_buffer);
    }

    return st;
}

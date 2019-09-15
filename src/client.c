#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
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
    if(!strncmp(CLIENT_CMD_VERIFY, buf, strlen(CLIENT_CMD_VERIFY))){
        return process_verify(socket);
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

status_t process_verify(socket_t *socket) {
    status_t st;

    if((st = ADT_socket_send(socket, SERVER_CMD_VERIFY, sizeof(SERVER_CMD_VERIFY))) != OK)
        return st;

    if((st = receive(socket)) != OK)
        return st;


    return OK;
}

status_t receive(socket_t *socket) {
    status_t st = OK;
    int res = 0;
    char *buffer;
    char *temp;
    int next_len;
    int next_res = 0;
    char *next_buffer;

    if((buffer = (char *) malloc(MAX_SMALL_BUF_LEN * sizeof(char))) == NULL)
        return ERROR_OUT_OF_MEMORY;

    if((st = ADT_socket_receive(socket, socket->file_descriptor, &res, &buffer, MAX_SMALL_BUF_LEN)) == OK) {

        next_len = (int) ntohs(strtol(buffer, &temp, 10));
        if((next_buffer = (char *) malloc((next_len + 1) * sizeof(char))) == NULL)
            return ERROR_OUT_OF_MEMORY;

        next_buffer[0] = '\0';
        printf("nexT_len: %d", next_len);

        if ((st = ADT_socket_receive(socket, socket->file_descriptor, &next_res, &next_buffer, next_len)) != OK) {
            return st;
        }
        next_buffer[next_res + 1] = '\0';

        printf("%s\n", next_buffer);
        free(next_buffer);
        next_buffer = NULL;
    }

    return st;
}

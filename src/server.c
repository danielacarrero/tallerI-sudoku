#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include "server.h"


status_t init_server(const char *service) {
    status_t st;
    server_t *server;

    if ((server = (server_t*)malloc(sizeof(server_t))) == NULL)
        return ERROR_OUT_OF_MEMORY;

    if ((st = init_socket(&(server->socket), service)) != OK)
        return st;

    if ((st = wait_and_receive(server)) != OK) {
        destroy_server(server);
        return st;
    }

    if ((st = destroy_server(server)) != OK)
        return st;

    return OK;
}

status_t init_socket(socket_t **socket, const char *service) {
    status_t st;
    struct addrinfo *addrinfo_res;

    if (service == NULL)
        return ERROR_NULL_POINTER;

    if((*socket = (socket_t*)malloc(sizeof(socket_t))) == NULL)
        return ERROR_OUT_OF_MEMORY;

    (*socket)->host = NULL;
    (*socket)->service = service;

    addrinfo_res = socket_init(*socket, SERVER);

    if ((st = socket_bind_and_listen(*socket, addrinfo_res)) != OK)
        return st;
    return OK;
}

status_t init_sudoku(sudoku_t **sudoku) {
    status_t st;
    FILE * fi;

    if (sudoku == NULL)
        return ERROR_NULL_POINTER;

    if ((fi = fopen(SUDOKU_FILE_PATH, "rt")) == NULL)
        return ERROR_OPENING_FILE;

    if((st = sudoku_init(sudoku, fi)) != OK) {
        fclose(fi);
        return st;
    }

    fclose(fi);
    return OK;
}

status_t destroy_server(server_t *server) {
    status_t st;

    if ((st = sudoku_destroy(server->sudoku)) != OK){
        socket_destroy(server->socket);
        return st;
    }

    if ((st = socket_destroy(server->socket)) != OK)
        return st;

    free(server->socket);
    server->socket = NULL;
    free(server);
    server = NULL;

    return OK;
}

status_t wait_and_receive(server_t *server) {
    status_t st = OK;
    int res = 0;
    char buffer[MAX_LENGTH_RECEIVED];
    bool connected = false;

    if ((st = socket_accept(server->socket)) != OK) {
        return st;
    }

    memset(buffer, 0, MAX_LENGTH_RECEIVED);

    while ((st = socket_receive(server->socket, &res, buffer, MAX_LENGTH_RECEIVED, MIN_LENGTH_RECEIVED)) != ERROR_CLOSED_SOCKET) {
        if (res != MAX_LENGTH_RECEIVED) {
            buffer[res + 1] = '\0';
        }

        if (!connected) {
            if ((st = init_sudoku(&(server->sudoku))) != OK){
                socket_destroy((server->socket));
                return st;
            }
            connected = true;
        }

        if((st = process_command_received(server, buffer)) != OK){
            print_error_msg(st);
            return st;
        }

        memset(buffer, 0, MAX_LENGTH_RECEIVED);
        res = 0;
    }

    return st;
}

status_t process_command_received(server_t *server, const char *buffer) {
    switch(buffer[0]) {
        case CMD_GET:
            return process_get_command(server);
        case CMD_PUT:
            return process_put_command(server, buffer);
        case CMD_RESET:
            return process_reset_command(server);
        case CMD_VERIFY:
            return process_verify_command(server);
        default:
            return ERROR_INVALID_DATA;
    }
}

status_t process_get_command(server_t *server) {
    status_t st;

    //printf("Processing GET command\n");
    char *printable;
    uint32_t max_table_send = htonl(LEN_MAX_SUDOKU_TABLE);
    char *size = (char *) &max_table_send;

    if((printable = (char *) malloc((LEN_MAX_SUDOKU_TABLE + 1) * sizeof(char))) == NULL)
        return ERROR_OUT_OF_MEMORY;
    printable[0] = '\0';

    if((st = sudoku_format_printable(server->sudoku, &printable, LEN_MAX_SUDOKU_TABLE)) != OK){
        return st;
    }

    if ((st = socket_send(server->socket, size, sizeof(uint32_t))) != OK)
        return st;

    if ((st = socket_send(server->socket, printable, strlen(printable))) != OK)
        return st;

    free(printable);
    printable = NULL;
    return OK;
}

status_t process_put_command(server_t *server, const char *buffer) {
    status_t st;

    //printf("Processing PUT command\n");
    size_t row = (size_t) buffer[ROW_PARAM_POS];
    size_t col = (size_t) buffer[COL_PARAM_POS];
    size_t value = (size_t) buffer[VALUE_PARAM_POS];

    st = sudoku_put_value(server->sudoku, row, col, value);

    if (st == ERROR_UNMODIFIABLE_CELL) {

        char *msg = MSG_ERROR_UNMODIFIABLE_CELL;
        unsigned long msg_size = strlen(msg);
        int32_t max_will_send = htonl(msg_size);
        char *size = (char *) &max_will_send;

        if ((st = socket_send(server->socket, size, sizeof(max_will_send))) != OK)
            return st;

        if ((st = socket_send(server->socket, msg, strlen(msg))) != OK)
            return st;

        return OK;

    } else if (st == OK) {
        if ((st = process_get_command(server)) != OK)
            return st;
    }

    return st;
}

status_t process_reset_command(server_t *server) {
    status_t st;

    //printf("Processing RESET command\n");

    if(((st = sudoku_reset(server->sudoku)) != OK))
        return st;
    if((st = process_get_command(server)) != OK)
        return st;

    return OK;
}

status_t process_verify_command(server_t *server) {
    status_t st;
    //printf("Processing VERIFY command\n");
    unsigned long msg_size;
    int32_t max_will_send;
    char *size = (char *) &max_will_send;

    char *msg = (sudoku_verify(server->sudoku) != OK) ? MSG_ERROR : MSG_OK;

    msg_size = strlen(msg);
    max_will_send = htonl(msg_size);

    if ((st = socket_send(server->socket, size, sizeof(max_will_send))) != OK)
        return st;

    if ((st = socket_send(server->socket, msg, strlen(msg))) != OK)
        return st;

    return OK;
}

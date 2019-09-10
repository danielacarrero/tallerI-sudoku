#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include "server.h"


status_t init_server(const char *service) {
    socket_t socket;
    sudoku_t *sudoku;
    status_t st;

    if((st = init_socket(&socket, service)) != OK)
        return st;
    fprintf(stdout, "%s\n", "Server inicializado! :)");

    if((st = init_sudoku(&sudoku)) != OK){
        ADT_socket_destroy(&socket);
        return st;
    }

    if ((st = wait_and_receive(&socket, sudoku)) != OK) {
        destroy_server(&socket, sudoku);
        return st;
    }

    if ((st = destroy_server(&socket, sudoku)) != OK)
        return st;

    return OK;
}

status_t init_socket(socket_t *socket, const char *service) {
    status_t st;
    printf("init socket\n");

    if (socket == NULL || service == NULL)
        return ERROR_NULL_POINTER;

    socket->host = NULL;
    socket->service = service;

    if ((st = ADT_socket_init(socket, SERVER)) != OK)
        return st;
    if ((st = ADT_socket_bind_and_listen(socket)) != OK)
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
    if((st = ADT_sudoku_init(sudoku, fi)) != OK) {
        fclose(fi);
        return st;
    }

    fclose(fi);
    return OK;
}

status_t destroy_server(socket_t *socket, sudoku_t *sudoku) {
    status_t st;
    if ((st = ADT_sudoku_destroy(sudoku)) != OK){
        ADT_socket_destroy(socket);
        return st;
    }
    if ((st = ADT_socket_destroy(socket)) != OK)
        return st;
    return OK;
}

status_t wait_and_receive(socket_t *socket, sudoku_t *sudoku) {
    status_t st = OK;
    int peer_fd = 0;
    int res = 0;
    char *buffer;

    if ((st = ADT_socket_accept(socket, &peer_fd)) != OK) {
        return st;
    }

    if((buffer = (char *) malloc(MAX_LENGTH_RECEIVED * sizeof(char))) == NULL)
        return ERROR_OUT_OF_MEMORY;
    memset(buffer, 0, MAX_LENGTH_RECEIVED);

    while ((st = ADT_socket_receive(socket, peer_fd, &res, &buffer, MAX_LENGTH_RECEIVED)) != ERROR_CLOSED_SOCKET) {
        if (res != MAX_LENGTH_RECEIVED) {
            buffer[res + 1] = '\0';
        }
        printf("buffer size: %d\n", res);
        printf("comando: %s\n", buffer);

        if((st = process_command_received(socket ,sudoku, buffer)) != OK){
            print_error_msg(st);
            return st;
        }

        memset(&buffer, 0, MAX_LENGTH_RECEIVED);
    }
    free(buffer);
    buffer = NULL;

    return st;
}

status_t process_command_received(socket_t *socket, sudoku_t *sudoku, const char *buffer) {
    switch(buffer[0]) {
        case CMD_GET:
            return process_get_command(socket, sudoku);
        case CMD_PUT:
            return process_put_command(socket, sudoku, buffer);
        case CMD_RESET:
            return process_reset_command(socket, sudoku);
        case CMD_VERIFY:
            return process_verify_command(socket, sudoku);
        default:
            return ERROR_INVALID_DATA;
    }
}

status_t process_get_command(socket_t *socket, sudoku_t *sudoku) {
    status_t st;

    printf("Processing GET command\n");
    char *printable;

    if((printable = (char *) malloc(LEN_MAX_SUDOKU_TABLE * sizeof(char))) == NULL)
        return ERROR_OUT_OF_MEMORY;
    printable[0] = '\0';

    if((st = ADT_sudoku_format_printable(sudoku, &printable, LEN_MAX_SUDOKU_TABLE)) != OK){
        return st;
    }
    printf("size of printable: %lu\n", strlen(printable));
    printf("%s\n", printable);
    char size[sizeof(strlen(printable))];
    snprintf(size, sizeof(strlen(printable)),"%du", htons(strlen(printable)));

    if ((st = ADT_socket_send(socket,  size, sizeof(size))) != OK)
        return st;

    if ((st = ADT_socket_send(socket, printable, strlen(printable))) != OK)
        return st;

    free(printable);
    printable = NULL;
    return OK;
}

status_t process_put_command(socket_t *socket, sudoku_t *sudoku, const char *buffer) {
    status_t st;

    printf("Processing PUT command\n");
    size_t row = (size_t) buffer[ROW_PARAM_POS] - 48;
    size_t col = (size_t) buffer[COL_PARAM_POS] - 48;
    size_t value = (size_t) buffer[VALUE_PARAM_POS] - 48;

    if((st = ADT_sudoku_put_value(sudoku, row, col, value)) != OK){
        return st;
    }
    if((st = process_get_command(socket, sudoku)) != OK)
        return st;

    return OK;
}

status_t process_reset_command(socket_t *socket, sudoku_t *sudoku) {
    status_t st;

    printf("Processing RESET command\n");

    if(((st = ADT_sudoku_reset(sudoku)) != OK))
        return st;
    if((st = process_get_command(socket, sudoku)) != OK)
        return st;

    return OK;
}

status_t process_verify_command(socket_t *socket, sudoku_t *sudoku) {
    status_t st;
    printf("Processing VERIFY command\n");

    if((st = ADT_sudoku_verify(sudoku)) != OK) {
        printf(MSG_ERROR);
    } else {
        printf(MSG_OK);
    }

    return OK;
}

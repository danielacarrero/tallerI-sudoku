#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "server.h"


status_t init_server(const char *service) {
    socket_t socket;
    sudoku_t sudoku;
    status_t st;

    if((st = init_socket(&socket, service)) != OK)
        return st;
    fprintf(stdout, "%s\n", "Server inicializado! :)");

    if((st = init_sudoku(&sudoku)) != OK){
        ADT_socket_destroy(&socket);
        return st;
    }

    if ((st = wait_and_receive(&socket, &sudoku)) != OK) {
        destroy_server(&socket, &sudoku);
        return st;
    }

    if ((st = destroy_server(&socket, &sudoku)) != OK)
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

status_t init_sudoku(sudoku_t *sudoku) {
    status_t st;
    FILE * fi;

    if (sudoku == NULL)
        return ERROR_NULL_POINTER;

    if ((fi = fopen(SUDOKU_FILE_PATH, "rt")) == NULL)
        return ERROR_OPENING_FILE;
    if((st = ADT_sudoku_init(&sudoku, fi)) != OK) {
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

        if((st = process_command_received(socket ,sudoku, buffer)) != OK){
            print_error_msg(st);
        }

        memset(&buffer, 0, MAX_LENGTH_RECEIVED);
    }

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
        printf("Hubo un error con printable.\n");
        return st;
    }

    printf("size of printable: %lu\n", strlen(printable));
    printf("%s\n", printable);

    free(printable);
    printable = NULL;
    return OK;
}

status_t process_put_command(socket_t *socket, sudoku_t *sudoku, const char *buffer) {
    printf("Processing PUT command\n");
    return OK;
}

status_t process_reset_command(socket_t *socket, sudoku_t *sudoku) {
    printf("Processing RESET command\n");
    return OK;
}

status_t process_verify_command(socket_t *socket, sudoku_t *sudoku) {
    printf("Processing VERIFY command\n");
    return OK;
}

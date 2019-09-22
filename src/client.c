#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "client.h"

status_t init_client(const char *host, const char *service) {
    client_t *client;
    struct addrinfo *addrinfo_res;
    status_t st;

    if ((client = (client_t*)malloc(sizeof(client_t))) == NULL)
        return ERROR_OUT_OF_MEMORY;

    if((client->socket = (socket_t*)malloc(sizeof(socket_t))) == NULL)
        return ERROR_OUT_OF_MEMORY;

    client->socket->host = host;
    client->socket->service = service;

    addrinfo_res = socket_init(client->socket, CLIENT);

    if ((st = socket_connect(client->socket, addrinfo_res)) != OK) {
        return st;
    }

    process_input(client);

    if ((st = destroy_client(client)) != OK) {
        return st;
    }

    return OK;
}

status_t destroy_client(client_t *client) {
    status_t st;

    st = socket_destroy(client->socket);

    free(client->socket);
    client->socket = NULL;
    free(client);
    client = NULL;

    return st;
}

void process_input(client_t *client) {
    status_t st;
    char buf[CMD_MAX_INPUT_SIZE];
    bool exit = false;

    while(!exit){
        if (fgets(buf, CMD_MAX_INPUT_SIZE, stdin) == NULL){
            return;
        }

        if (!strncmp(CLIENT_CMD_EXIT, buf, strlen(CLIENT_CMD_EXIT))){
            exit = true;
        }

        if ((st = process_command(client, buf)) != OK)
            print_error_msg(st);
    }
}

status_t process_command(client_t *client, char *buf) {

    if (!strncmp(CLIENT_CMD_GET, buf, strlen(CLIENT_CMD_GET))){
        return process_get(client);
    }
    if (!strncmp(CLIENT_CMD_VERIFY, buf, strlen(CLIENT_CMD_VERIFY))){
        return process_verify(client);
    }
    if (!strncmp(CLIENT_CMD_RESET, buf, strlen(CLIENT_CMD_RESET))){
        return process_reset(client);
    }
    if (!strncmp(CLIENT_CMD_PUT, buf, strlen(CLIENT_CMD_PUT))) {
        return process_put(client, buf);
    }
    return ERROR_INVALID_DATA;
}

status_t process_get(client_t *client) {
    status_t st;

    if((st = socket_send(client->socket, SERVER_CMD_GET, sizeof(SERVER_CMD_GET))) != OK)
        return st;

    if((st = receive(client)) != OK)
        return st;

    return OK;
}

status_t process_verify(client_t *client) {
    status_t st;

    if ((st = socket_send(client->socket, SERVER_CMD_VERIFY, sizeof(SERVER_CMD_VERIFY))) != OK)
        return st;

    if ((st = receive(client)) != OK)
        return st;


    return OK;
}

status_t process_reset(client_t *client) {
    status_t st;

    if ((st = socket_send(client->socket, SERVER_CMD_RESET, sizeof(SERVER_CMD_RESET))) != OK)
        return st;

    if ((st = receive(client)) != OK)
        return st;

    return OK;
}

status_t process_put(client_t *client, const char *buffer) {
    status_t st;
    uint8_t row = 0;
    uint8_t col = 0;
    uint8_t value = 0;
    size_t argNum = 0;
    char *iter;
    char *colRow = "";
    char *temp;
    char auxBuffer[CMD_MAX_INPUT_SIZE];
    char msg[SERVER_MAX_PUT_LEN];

    memcpy(auxBuffer, buffer, CMD_MAX_INPUT_SIZE);

    iter = strtok(auxBuffer, CMD_PUT_DELIMITER);
    while(iter != NULL) {
        if (argNum == 1)
            value = (uint8_t) strtol(iter, &temp, 10);
        if (argNum == 3)
            colRow = iter;
        iter = strtok(NULL, CMD_PUT_DELIMITER);
        argNum ++;
    }

    argNum = 0;
    iter = strtok(colRow, CMD_PUT_COL_ROW_DELIM);
    while(iter != NULL) {
        if (argNum == 0)
            row = (uint8_t) strtol(iter, &temp, 10);
        if (argNum == 1)
            col = (uint8_t) strtol(iter, &temp, 10);
        iter = strtok(NULL, CMD_PUT_COL_ROW_DELIM);
        argNum ++;
    }

    if ((st = (validate_put_arguments(value, row, col))) != OK)
        return st;

    msg[0] = SERVER_CMD_PUT[0];
    msg[1] = ((char *) &row)[0];
    msg[2] = ((char *) &col)[0];
    msg[3] = ((char * ) &value)[0];

    if ((st = socket_send(client->socket, msg, SERVER_MAX_PUT_LEN)) != OK)
        return st;

    if ((st = receive(client)) != OK)
        return st;

    return OK;
}

status_t validate_put_arguments(uint8_t value, uint8_t row, uint8_t col) {

    if (row <= 0 || row >= 10 ||
        col <= 0 || col >= 10)
        return ERROR_UNSUPPORTED_INDICES;

    if (value <= 0 || value >= 10)
        return ERROR_UNSUPPORTED_VALUE;

    return OK;
}

status_t receive(client_t *client) {
    status_t st = OK;
    int res = 0;
    int next_res = 0;
    char *next_buffer;
    long next_read_len;
    int32_t buff_len;

    if ((st = socket_receive(client->socket, &res,
                             (char *) &buff_len, sizeof(buff_len),
                             sizeof(buff_len))) == OK) {

        next_read_len = ntohl(buff_len);
        if((next_buffer = (char *) malloc((next_read_len + 2) * sizeof(char))) == NULL)
            return ERROR_OUT_OF_MEMORY;

        memset(next_buffer, 0, next_read_len + 2);

        if ((st = socket_receive(client->socket, &next_res,
                                 next_buffer, next_read_len, next_read_len)) != OK) {
            return st;
        }
        next_buffer[next_res + 1] = '\0';

        printf("%s\n", next_buffer);
        free(next_buffer);
        next_buffer = NULL;
    }

    return st;
}

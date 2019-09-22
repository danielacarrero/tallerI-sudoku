#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "client.h"

status_t init_client(const char *host, const char *service) {
    client_t *client;
    struct addrinfo *addrinfo_res;
    status_t st = OK;

    client = (client_t*)malloc(sizeof(client_t));
    if (client == NULL)
        return ERROR_OUT_OF_MEMORY;

    client->socket = (socket_t*)malloc(sizeof(socket_t));
    if (client->socket == NULL)
        return ERROR_OUT_OF_MEMORY;

    client->socket->host = host;
    client->socket->service = service;

    addrinfo_res = socket_init(client->socket, CLIENT);

    st = socket_connect(client->socket, addrinfo_res);
    if (st != OK)
        return st;

    process_input(client);

    st = destroy_client(client);
    return st;
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

    while (!exit){
        if (fgets(buf, CMD_MAX_INPUT_SIZE, stdin) == NULL)
            return;

        if (!strncmp(CLIENT_CMD_EXIT, buf, strlen(CLIENT_CMD_EXIT)))
            exit = true;

        st = process_command(client, buf);
        if (st != OK)
            print_error_msg(st);
    }
}

status_t process_command(client_t *client, char *buf) {
    if (!strncmp(CLIENT_CMD_GET, buf, strlen(CLIENT_CMD_GET)))
        return process_get(client);
    if (!strncmp(CLIENT_CMD_VERIFY, buf, strlen(CLIENT_CMD_VERIFY)))
        return process_verify(client);
    if (!strncmp(CLIENT_CMD_RESET, buf, strlen(CLIENT_CMD_RESET)))
        return process_reset(client);
    if (!strncmp(CLIENT_CMD_PUT, buf, strlen(CLIENT_CMD_PUT)))
        return process_put(client, buf);
    return ERROR_INVALID_DATA;
}

status_t process_get(client_t *client) {
    status_t st;

    st = socket_send(client->socket, SERVER_CMD_GET, sizeof(SERVER_CMD_GET));
    if (st != OK)
        return st;

    st = receive(client);
    if (st != OK)
        return st;

    return OK;
}

status_t process_verify(client_t *client) {
    status_t st;

    st = socket_send(client->socket,
            SERVER_CMD_VERIFY,
            sizeof(SERVER_CMD_VERIFY));
    if (st != OK)
        return st;

    if ((st = receive(client)) != OK)
        return st;


    return OK;
}

status_t process_reset(client_t *client) {
    status_t st;

    st = socket_send(client->socket,
            SERVER_CMD_RESET,
            sizeof(SERVER_CMD_RESET));
    if (st != OK)
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
    char *auxBufferTemp = auxBuffer;
    char *colRowTemp = colRow;
    char msg[SERVER_MAX_PUT_LEN];

    memcpy(auxBuffer, buffer, CMD_MAX_INPUT_SIZE);

    iter = strtok_r(auxBuffer, CMD_PUT_DELIMITER, &auxBufferTemp);
    while (iter != NULL) {
        if (argNum == 1)
            value = (uint8_t) strtol(iter, &temp, 10);
        if (argNum == 3)
            colRow = iter;
        iter = strtok_r(NULL, CMD_PUT_DELIMITER, &auxBufferTemp);
        argNum ++;
    }

    argNum = 0;
    iter = strtok_r(colRow, CMD_PUT_COL_ROW_DELIM, &colRowTemp);
    while (iter != NULL) {
        if (argNum == 0)
            row = (uint8_t) strtol(iter, &temp, 10);
        if (argNum == 1)
            col = (uint8_t) strtol(iter, &temp, 10);
        iter = strtok_r(NULL, CMD_PUT_COL_ROW_DELIM, &colRowTemp);
        argNum ++;
    }

    st = (validate_put_arguments(value, row, col));
    if (st != OK)
        return st;

    msg[0] = SERVER_CMD_PUT[0];
    msg[1] = ((char *) &row)[0];
    msg[2] = ((char *) &col)[0];
    msg[3] = ((char * ) &value)[0];

    st = socket_send(client->socket, msg, SERVER_MAX_PUT_LEN);
    if (st != OK)
        return st;

    st = receive(client);
    if (st != OK)
        return st;

    return OK;
}

c

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

        next_buffer = (char *) malloc((next_read_len + 2) * sizeof(char));
        if (next_buffer == NULL)
            return ERROR_OUT_OF_MEMORY;

        memset(next_buffer, 0, next_read_len + 2);

        st = socket_receive(client->socket,
                           &next_res,
                           next_buffer,
                           next_read_len,
                           next_read_len);
        if (st != OK) {
            return st;
        }
        next_buffer[next_res + 1] = '\0';

        printf("%s", next_buffer);
        free(next_buffer);
        next_buffer = NULL;
    }

    return st;
}

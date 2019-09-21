#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <stdbool.h>
#include <errno.h>
#include <stdlib.h>

#include "adt_socket.h"

status_t ADT_socket_init(socket_t *adt_socket, socket_type_t type) {
    struct addrinfo hints;
    int res;

    if (adt_socket == NULL)
        return ERROR_NULL_POINTER;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = (type == SERVER) ? AI_PASSIVE : CLIENT;
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;

    if ((res = getaddrinfo(adt_socket->host, adt_socket->service,
            &hints, &(adt_socket->addrinfo_res))) != GETADDRINFO_SUCCESSFUL) {
        perror(gai_strerror(res));
        return ERROR_INVALID_DATA;
    }

    return OK;
}

status_t ADT_socket_destroy(socket_t *adt_socket) {
    if (adt_socket == NULL)
        return ERROR_NULL_POINTER;

    shutdown(adt_socket->file_descriptor, SHUT_RDWR);
    close(adt_socket->file_descriptor);
    return OK;
}

status_t ADT_socket_connect(socket_t *adt_socket) {
    int res;
    int fd;
    bool connected = false;
    struct addrinfo *iterator;

    if (adt_socket == NULL)
        return ERROR_NULL_POINTER;

    for (iterator = adt_socket->addrinfo_res; iterator != NULL && connected == false; iterator = iterator->ai_next) {
        fd = socket(iterator->ai_family, iterator->ai_socktype, iterator->ai_protocol);
        if (fd == INVALID_FD)
            continue;

        res = connect(fd, iterator->ai_addr, iterator->ai_addrlen);
        if (res == INVALID_FD) {
            printf("Error: %s\n", strerror(errno));
            close(fd);
        } else {
            adt_socket->file_descriptor = fd;
            connected = true;
        }
    }

    freeaddrinfo(adt_socket->addrinfo_res);
    if (!connected)
        return ERROR_SOCKET_CONNECTION;

    return OK;
}

status_t ADT_socket_bind_and_listen(socket_t *adt_socket) {
    int res;
    int fd;

    if(adt_socket == NULL)
        return ERROR_NULL_POINTER;

    fd = socket(adt_socket->addrinfo_res->ai_family, adt_socket->addrinfo_res->ai_socktype, adt_socket->addrinfo_res->ai_protocol);
    if (fd == INVALID_FD)
        return ERROR_SOCKET_BINDING_AND_LISTEN;

    adt_socket->file_descriptor = fd;

    res = bind(adt_socket->file_descriptor, adt_socket->addrinfo_res->ai_addr, adt_socket->addrinfo_res->ai_addrlen);
    freeaddrinfo(adt_socket->addrinfo_res);

    if (res == ERROR_SOCKET) {
        printf("Error: %s\n", strerror(errno));
        close(adt_socket->file_descriptor);
        return ERROR_SOCKET_BINDING_AND_LISTEN;
    }
    
    res = listen(adt_socket->file_descriptor, MAX_CONNECTIONS);
    if (res == ERROR_SOCKET) {
        printf("Error: %s\n", strerror(errno));
        close(adt_socket->file_descriptor);
        return ERROR_SOCKET_BINDING_AND_LISTEN;
    }

    return OK;
}

status_t ADT_socket_send(socket_t *adt_socket, const char *buffer, size_t length) {
    printf("sending\n");
    int sent = 0;
    int res = 0;

    if(adt_socket == NULL || buffer == NULL)
        return ERROR_NULL_POINTER;

    while(sent < length) {
        res = send(adt_socket->file_descriptor, &buffer[sent], length - sent, 0); //TODO: MSG_NOSIGNAL (no está en macOS)
        if (res == CLOSED_SOCKET) {
            return ERROR_CLOSED_SOCKET;
        } else if (res == ERROR_SOCKET) {
            printf("Error: %s\n", strerror(errno));
            return ERROR_SOCKET_SENDING;
        } else {
            sent += res;
            fprintf(stdout, "Enviando %i/%zu bytes\n", res, length);
        }
    }

    return OK;
}

status_t ADT_socket_receive(socket_t *adt_socket, int peer_fd, int *received, char *buffer, size_t length, size_t min_length) {
    int res = 0;
    long buff_len = 0;
    char *temp;
    status_t st = OK;

    if (adt_socket == NULL || buffer == NULL)
        return ERROR_NULL_POINTER;

    memset(buffer, 0, length);

    while(*received < length) {
        res = recv(peer_fd, &buffer[*received], length - *received, 0);

        if (res == CLOSED_SOCKET) {
            shutdown(peer_fd, SHUT_RDWR);
            close(peer_fd);
            st = ERROR_CLOSED_SOCKET;
            break;
        } else if (res == ERROR_SOCKET) {
            printf("Error: %s\n", strerror(errno));
            shutdown(peer_fd, SHUT_RDWR);
            close(peer_fd);
            st = ERROR_SOCKET_RECEIVING;
            break;
        } else {
            fprintf(stdout, "Recibiendo %i/%zu bytes\n", res, length);
            *received += res;

            buff_len = strtol(buffer, &temp, 10);
            if (buff_len == 0 && *received >= min_length) {
                printf("Recibiendo 0 bytes.\n");
                break;
            }
        }
    }

    return st;
}

status_t ADT_socket_accept(socket_t *adt_socket, int *peer_fd) {

    if(adt_socket == NULL || peer_fd == NULL)
        return ERROR_NULL_POINTER;

    *peer_fd = accept(adt_socket->file_descriptor, NULL, NULL);
    adt_socket->file_descriptor = *peer_fd;

    if (*peer_fd == INVALID_FD) {
        printf("Error: %s\n", strerror(errno));
        ADT_socket_destroy(adt_socket);
        return ERROR_ACCEPTING_SOCKET_CONNECTION;
    }

    return OK;
}

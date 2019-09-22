#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <stdbool.h>
#include <errno.h>
#include <stdlib.h>

#include "socket.h"

 struct addrinfo * socket_init(socket_t *sckt, socket_type_t type) {
    struct addrinfo hints;
    struct addrinfo *addrinfo_res;
    int res;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = (type == SERVER) ? AI_PASSIVE : CLIENT;
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;

    if ((res = getaddrinfo(sckt->host, sckt->service,
                           &hints, &addrinfo_res)) != GETADDRINFO_SUCCESSFUL) {
        perror(gai_strerror(res));
    }

    return addrinfo_res;
}

status_t socket_create(socket_t *sckt, struct addrinfo *addrinfo_res) {
    int fd = 0;

    fd = socket(addrinfo_res->ai_family,
              addrinfo_res->ai_socktype,
              addrinfo_res->ai_protocol);

    if (fd == INVALID_FD)
        return ERROR_INVALID_DATA;

    sckt->file_descriptor = fd;

    return OK;
}

status_t socket_destroy(socket_t *sckt) {
    if (sckt == NULL)
        return ERROR_NULL_POINTER;

    shutdown(sckt->file_descriptor, SHUT_RDWR);
    close(sckt->file_descriptor);

    return OK;
}

status_t socket_connect(socket_t *sckt, struct addrinfo *addrinfo_res) {
    int res;
    bool connected = false;
    struct addrinfo *iterator;

    if (sckt == NULL)
        return ERROR_NULL_POINTER;

    for (iterator = addrinfo_res; iterator != NULL && connected == false; iterator = iterator->ai_next) {
        if (socket_create(sckt, addrinfo_res) != OK) {
            continue;
        }

        res = connect(sckt->file_descriptor, iterator->ai_addr, iterator->ai_addrlen);
        if (res == INVALID_FD) {
            printf("Error: %s\n", strerror(errno));
            close(sckt->file_descriptor);
            sckt->file_descriptor = 0;
        } else {
            connected = true;
        }
    }

    freeaddrinfo(addrinfo_res);
    if (!connected)
        return ERROR_SOCKET_CONNECTION;

    return OK;
}

status_t socket_bind_and_listen(socket_t *sckt, struct addrinfo *addrinfo_res) {
    int res;

    if (sckt == NULL)
        return ERROR_NULL_POINTER;

    if (socket_create(sckt, addrinfo_res) != OK)
        return ERROR_SOCKET_BINDING_AND_LISTEN;

    res = bind(sckt->file_descriptor, addrinfo_res->ai_addr, addrinfo_res->ai_addrlen);
    freeaddrinfo(addrinfo_res);

    if (res == ERROR_SOCKET) {
        printf("Error: %s\n", strerror(errno));
        close(sckt->file_descriptor);
        return ERROR_SOCKET_BINDING_AND_LISTEN;
    }
    
    res = listen(sckt->file_descriptor, MAX_CONNECTIONS);
    if (res == ERROR_SOCKET) {
        printf("Error: %s\n", strerror(errno));
        close(sckt->file_descriptor);
        return ERROR_SOCKET_BINDING_AND_LISTEN;
    }

    return OK;
}

status_t socket_send(socket_t *sckt, const char *buffer, size_t length) {
    int sent = 0;
    int res = 0;

    if (sckt == NULL || buffer == NULL)
        return ERROR_NULL_POINTER;

    while (sent < length) {
        res = send(sckt->file_descriptor, &buffer[sent], length - sent, 0); //TODO: MSG_NOSIGNAL (no está en macOS)
        if (res == CLOSED_SOCKET) {
            return ERROR_CLOSED_SOCKET;
        } else if (res == ERROR_SOCKET) {
            printf("Error: %s\n", strerror(errno));
            return ERROR_SOCKET_SENDING;
        } else {
            sent += res;
            //fprintf(stdout, "Enviando %i/%zu bytes\n", res, length);
        }
    }

    return OK;
}

status_t socket_receive(socket_t *sckt, int *received, char *buffer, size_t length, size_t min_length) {
    int res = 0;
    long buff_len = 0;
    char *temp;
    status_t st = OK;

    if (sckt == NULL || buffer == NULL)
        return ERROR_NULL_POINTER;

    memset(buffer, 0, length);

    while (*received < length) {
        res = recv(sckt->file_descriptor, &buffer[*received], length - *received, 0);

        if (res == CLOSED_SOCKET) {
            shutdown(sckt->file_descriptor, SHUT_RDWR);
            close(sckt->file_descriptor);
            st = ERROR_CLOSED_SOCKET;
            break;
        } else if (res == ERROR_SOCKET) {
            printf("Error: %s\n", strerror(errno));
            shutdown(sckt->file_descriptor, SHUT_RDWR);
            close(sckt->file_descriptor);
            st = ERROR_SOCKET_RECEIVING;
            break;
        } else {
            //fprintf(stdout, "Recibiendo %i/%zu bytes\n", res, length);
            *received += res;

            buff_len = strtol(buffer, &temp, 10);
            if (buff_len == 0 && *received >= min_length) {
                //printf("Recibiendo 0 bytes.\n");
                break;
            }
        }
    }

    return st;
}

status_t socket_accept(socket_t *sckt) {
    int peer_fd = 0;

    if (sckt == NULL)
        return ERROR_NULL_POINTER;

    peer_fd = accept(sckt->file_descriptor, NULL, NULL);
    sckt->file_descriptor = peer_fd;

    if (peer_fd == INVALID_FD) {
        printf("Error: %s\n", strerror(errno));
        socket_destroy(sckt);
        return ERROR_ACCEPTING_SOCKET_CONNECTION;
    }

    return OK;
}

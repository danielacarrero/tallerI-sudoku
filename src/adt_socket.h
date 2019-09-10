#ifndef ADT_SOCKET__H
#define ADT_SOCKET__H

#define _POSIX_C_SOURCE 200112L

#include <netdb.h>
#include "types.h"

#define INVALID_FD -1
#define GETADDRINFO_SUCCESSFUL 0
#define ERROR_SOCKET -1
#define CLOSED_SOCKET 0
#define MAX_CONNECTIONS 20

typedef struct {
    int file_descriptor;
    const char *host;
    const char *service;
    struct addrinfo *addrinfo_res;
} socket_t;

status_t ADT_socket_init(socket_t *socket, socket_type_t type);
status_t ADT_socket_destroy(socket_t *socket);
status_t ADT_socket_send(socket_t *socket, const char *buffer, size_t length);
status_t ADT_socket_receive(socket_t *socket, int peer_fd, int *res, char **buffer, size_t length);
status_t ADT_socket_connect(socket_t *socket);
status_t ADT_socket_bind_and_listen(socket_t *socket);
status_t ADT_socket_accept(socket_t *socket, int *peer_fd);

#endif

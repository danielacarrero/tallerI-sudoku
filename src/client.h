#ifndef CLIENT__H
#define CLIENT__H

#include "types.h"
#include "errors.h"
#include "adt_socket.h"

#define CMD_MAX_INPUT_SIZE 15
#define MAX_SMALL_BUF_LEN 5
#define CLIENT_CMD_EXIT "exit"
#define CLIENT_CMD_GET "get"
#define CLIENT_CMD_PUT "put"
#define CLIENT_CMD_VERIFY "verify"
#define CLIENT_CMD_RESET "reset"
#define SERVER_CMD_GET "G"
#define SERVER_CMD_PUT "P"
#define SERVER_CMD_VERIFY "V"
#define SERVER_CMD_RESET "R"

status_t init_client(const char *host, const char *service);
void process_input(socket_t *socket);
status_t process_command(socket_t *socket, char *buf);
status_t receive(socket_t *socket);
status_t process_get(socket_t *socket);

#endif

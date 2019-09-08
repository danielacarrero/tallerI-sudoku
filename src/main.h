#ifndef MAIN__H
#define MAIN__H

#include <stdio.h>
#include "types.h"
#include "errors.h"
#include "client.h"
#include "server.h"


#define CMD_ARG_MINIMUM_NUMBER 2
#define CMD_ARG_SOCKET_TYPE_POSITION 1

#define CMD_ARG_SERVER_TYPE "server"
#define CMD_ARG_SERVER_NUMBER 3
#define CMD_ARG_SERVER_PORT_POSITION 2

#define CMD_ARG_CLIENT_TYPE "client"
#define CMD_ARG_CLIENT_NUMBER 4
#define CMD_ARG_CLIENT_HOST_POSITION 2
#define CMD_ARG_CLIENT_PORT_POSITION 3

#define ERROR 1
#define SUCCESSFUL 0

status_t validate_arguments(int argc, char *argv[]);
bool is_client(char *argv[]);
bool is_server(char *argv[]);

#endif

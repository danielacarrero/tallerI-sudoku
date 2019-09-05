#ifndef MAIN__H
#define MAIN__H

#include <stdio.h>
#include "types.h"
#include "errors.h"

#define CMD_ARG_MINIMUM_NUMBER 2
#define CMD_ARG_SERVER_NUMBER 3
#define CMD_ARG_CLIENT_NUMBER 4
#define CMD_ARG_SOCKET_TYPE_POSITION 1
#define CMD_ARG_SERVER_TYPE "server"
#define CMD_ARG_CLIENT_TYPE "client"

#define ERROR 1
#define SUCCESSFUL 0

status_t validate_arguments(int argc, char *argv[]);

#endif

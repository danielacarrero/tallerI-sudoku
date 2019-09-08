#ifndef CLIENT__H
#define CLIENT__H

#include "types.h"
#include "adt_socket.h"

#define CMD_MAX_INPUT_SIZE 15
#define CMD_EXIT "exit"

status_t init_client(const char *host, const char *service);
void process_input();

#endif

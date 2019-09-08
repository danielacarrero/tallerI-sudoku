#ifndef SERVER__H
#define SERVER__H

#include "types.h"
#include "adt_socket.h"

#define MAX_LENGTH_RECEIVED 4

status_t init_server(const char *port);

#endif

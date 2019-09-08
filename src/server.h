#ifndef SERVER__H
#define SERVER__H

#include "types.h"
#include "adt_socket.h"
#include "errors.h"

#define MAX_LENGTH_RECEIVED 5

#define CMD_GET 'G'
#define CMD_PUT 'P'
#define CMD_VERIFY 'V'
#define CMD_RESET 'R'

status_t init_server(const char *service);
status_t wait_and_receive(socket_t *socket);
status_t process_command_received(const char *buffer);
status_t process_get_command();
status_t process_put_command(const char *buffer);
status_t process_reset_command();
status_t process_verify_command();

#endif

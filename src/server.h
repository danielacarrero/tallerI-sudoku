#ifndef SERVER__H
#define SERVER__H

#include "types.h"
#include "socket.h"
#include "errors.h"
#include "sudoku.h"

#define MAX_LENGTH_RECEIVED 5
#define MIN_LENGTH_RECEIVED 2

#define SUDOKU_FILE_PATH "../src/board.txt"
#define CMD_GET 'G'
#define CMD_PUT 'P'
#define CMD_VERIFY 'V'
#define CMD_RESET 'R'
#define ROW_PARAM_POS 1
#define COL_PARAM_POS 2
#define VALUE_PARAM_POS 3

typedef struct {
    socket_t *socket;
    sudoku_t *sudoku;
} server_t;

status_t init_server(const char *service);
status_t init_socket(socket_t **socket, const char *service);
status_t init_sudoku(sudoku_t **sudoku);
status_t destroy_server(server_t *server);
status_t wait_and_receive(server_t *server);
status_t process_command_received(server_t *server, const char *buffer);
status_t process_get_command(server_t *server);
status_t process_put_command(server_t *server, const char *buffer);
status_t process_reset_command(server_t *server);
status_t process_verify_command(server_t *server);

#endif

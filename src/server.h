#ifndef SERVER__H
#define SERVER__H

#include "types.h"
#include "adt_socket.h"
#include "errors.h"
#include "adt_sudoku.h"

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

status_t init_server(const char *service);
status_t init_socket(socket_t *socket, const char *service);
status_t init_sudoku(sudoku_t **sudoku);
status_t destroy_server(socket_t *socket, sudoku_t *sudoku);
status_t wait_and_receive(socket_t *socket, sudoku_t *sudoku);
status_t process_command_received(socket_t *socket, sudoku_t *sudoku, const char *buffer);
status_t process_get_command(socket_t *socket, sudoku_t *sudoku);
status_t process_put_command(socket_t *socket, sudoku_t *sudoku, const char *buffer);
status_t process_reset_command(socket_t *socket, sudoku_t *sudoku);
status_t process_verify_command(socket_t *socket, sudoku_t *sudoku);

#endif

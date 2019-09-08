#ifndef ADT_SUDOKU__H
#define ADT_SUDOKU__H

#include <stdint.h>
#include "types.h"

#define MAX_NUM_ROWS 9
#define MAX_NUM_COLS 9
#define MAX_NUM_CELLS 81

typedef struct {
    uint8_t row;
    uint8_t col;
    uint8_t value;
} cell_t;

typedef struct {
    cell_t initial_cells[MAX_NUM_CELLS];
    cell_t current_cells[MAX_NUM_CELLS];
} sudoku_t;

status_t ADT_sudoku_init(sudoku_t *sudoku, FILE * fi );
status_t ADT_sudoku_format_printable(sudoku_t *sudoku, char *printable);

#endif

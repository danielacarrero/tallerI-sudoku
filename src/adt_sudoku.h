#ifndef ADT_SUDOKU__H
#define ADT_SUDOKU__H

#include <stdint.h>
#include "types.h"
#include "adt_vector.h"

#define LEN_MAX_NUMBER 2
#define LEN_MAX_SUDOKU_LINE 19
#define LEN_MAX_SUDOKU_TABLE 722
#define SUDOKU_BIG_CELL_LIMIT_ROW "U===========U===========U===========U"
#define SUDOKU_LIMIT_ROW "U---+---+---U---+---+---U---+---+---U"
#define SUDOKU_BIG_CELL_LIMIT_COL " U "
#define SUDOKU_INIT_TABLE_ROW "U "
#define SUDOKU_LIMIT_COL " | "
#define SUDOKU_EMPTY_CELL " "
#define SUDOKU_MAX_NUM_TABLE_ROWS 19
#define SUDOKU_MAX_NUM_TABLE_COLS 37
#define SUDOKU_NEXT_ROW_DELIM "\n"
#define DELIMITER_SUDOKU " "
#define EMPTY_CELL 0
#define MAX_NUM_COLS 9
#define MAX_NUM_CELLS 81

typedef struct {
    uint8_t row;
    uint8_t col;
    uint8_t value;
} cell_t;

typedef struct {
    vector_t *initial_cells;
    vector_t *current_cells;
} sudoku_t;

status_t ADT_sudoku_init(sudoku_t *sudoku, FILE * fi );
status_t ADT_sudoku_add_initial_cell(sudoku_t * sudoku, uint8_t row, uint8_t col, uint8_t value);
status_t ADT_sudoku_destroy(sudoku_t *sudoku);
status_t ADT_sudoku_format_printable(const sudoku_t *sudoku, char **printable, size_t size);
bool ADT_sudoku_compare_cells(const void *c1, const void *c2);
bool ADT_sudoku_compare_cell_position(const void *c1, const void *c2);

#endif

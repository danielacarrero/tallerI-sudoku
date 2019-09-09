#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "adt_sudoku.h"

status_t ADT_sudoku_init(sudoku_t **sudoku, FILE * fi ) {
    char row_line[LEN_MAX_SUDOKU_LINE];
    char *iter;
    char *temp;
    bool eof = false;
    size_t row = 1;
    size_t col;
    size_t value;

    if (sudoku == NULL || fi == NULL)
        return ERROR_NULL_POINTER;
    if((*sudoku = (sudoku_t*)malloc(sizeof(sudoku_t))) == NULL)
        return ERROR_OUT_OF_MEMORY;
    if (ADT_vector_create(&((*sudoku)->initial_cells)) != OK)
        return ERROR_CREATING_SUDOKU;
    if (ADT_vector_create(&((*sudoku)->current_cells)) != OK)
        return ERROR_CREATING_SUDOKU;

    while(!eof){
        col = 1;
        if (fgets(row_line, LEN_MAX_SUDOKU_LINE, fi) == NULL) {
            eof = true;
        }
        iter = strtok(row_line, DELIMITER_SUDOKU);
        while (iter != NULL && !eof) {
            value = (size_t) strtol(iter, &temp, 10);
            if (ADT_sudoku_add_initial_cell(*sudoku, row, col, value) != OK){
                return ERROR_CREATING_SUDOKU;
            }
            iter = strtok(NULL, DELIMITER_SUDOKU);
            col ++;
        }
        row ++;
    }
    return OK;
}

status_t ADT_sudoku_add_initial_cell(sudoku_t * sudoku, size_t row, size_t col, size_t value) {
    cell_t *new_cell;
    cell_t *new_cell2;
    status_t st;

    if (sudoku == NULL)
        return ERROR_NULL_POINTER;
    if (value == EMPTY_CELL)
        return OK;
    if((new_cell = (cell_t*)malloc(sizeof(cell_t))) == NULL)
        return ERROR_OUT_OF_MEMORY;
    if((new_cell2 = (cell_t*)malloc(sizeof(cell_t))) == NULL)
        return ERROR_OUT_OF_MEMORY;

    new_cell->row = row;
    new_cell->col = col;
    new_cell->value = value;
    *new_cell2 = *new_cell;

    if ((st = ADT_vector_append(sudoku->initial_cells, new_cell)) != OK)
        return st;
    if ((st = ADT_vector_append(sudoku->current_cells, new_cell2)) != OK)
        return st;

    return OK;
}

status_t ADT_sudoku_destroy(sudoku_t *sudoku) {
    status_t st;

    if (sudoku == NULL)
        return ERROR_NULL_POINTER;
    if ((st = ADT_Vector_set_destructor(sudoku->initial_cells, ADT_cell_destroy)) != OK)
        return st;
    if ((st = ADT_Vector_set_destructor(sudoku->current_cells, ADT_cell_destroy)) != OK)
        return st;
    if ((st = ADT_vector_destroy((void *) &(sudoku->initial_cells))) != OK)
        return st;
    if ((st = ADT_vector_destroy((void*) &(sudoku->current_cells))) != OK)
        return st;

    free(sudoku);
    sudoku = NULL;

    printf("Sudoku destruido!\n");
    return OK;
}

status_t ADT_sudoku_format_printable(const sudoku_t *sudoku, char **printable, size_t size) {
    size_t row = 1;
    size_t col = 1;
    cell_t search_cell;
    cell_t *result_cell;
    size_t printable_len = size;
    char cell_number[LEN_MAX_NUMBER];

    if (sudoku == NULL || printable == NULL)
        return ERROR_NULL_POINTER;

    if (ADT_vector_set_searcher(sudoku->current_cells, ADT_sudoku_compare_cell_position) != OK)
        return ERROR_FORMATTING_SUDOKU;

    strncat(*printable, SUDOKU_BIG_CELL_LIMIT_ROW, printable_len);
    for (size_t t_row = 1; t_row <= SUDOKU_MAX_NUM_TABLE_ROWS; t_row ++) {
        if(t_row % 6 == 0) {
            strncat(*printable, SUDOKU_BIG_CELL_LIMIT_ROW, printable_len);
        } else if(t_row % 2){
            strncat(*printable, SUDOKU_INIT_TABLE_ROW, printable_len);
            for(col = 1; col <= MAX_NUM_COLS; col ++) {
                search_cell.row = row;
                search_cell.col = col;

                result_cell = (cell_t *) ADT_vector_search(sudoku->current_cells, &search_cell);
                if (result_cell == NULL){
                    strncat(*printable, SUDOKU_EMPTY_CELL, printable_len);
                } else {
                    snprintf(cell_number, LEN_MAX_NUMBER,"%zu", (size_t) result_cell->value);
                    strncat(*printable, cell_number, printable_len);
                }

                if (col == MAX_NUM_COLS) {
                    strncat(*printable, SUDOKU_FINISH_TABLE_ROW, printable_len);
                } else if (col % 3 == 0){
                    strncat(*printable, SUDOKU_BIG_CELL_LIMIT_COL, printable_len);
                } else {
                    strncat(*printable, SUDOKU_LIMIT_COL, printable_len);
                }
            }
            row ++;
        } else {
            strncat(*printable, SUDOKU_LIMIT_ROW, printable_len);
        }

    }
    return OK;
}

bool ADT_sudoku_compare_cells(const void *c1, const void *c2) {
    cell_t *cell1 = (cell_t *) c1;
    cell_t *cell2 = (cell_t *) c2;

    if(cell1->value == cell2->value
        && cell1->col == cell2->col
        && cell1->row == cell2->row)
        return true;

    return false;
}

bool ADT_sudoku_compare_cell_position(const void *c1, const void *c2) {
    cell_t *cell1 = (cell_t *) c1;
    cell_t *cell2 = (cell_t *) c2;

    if(cell1 == NULL || cell2 == NULL)
        return false;

    if ( cell1->col == cell2->col
        && cell1->row == cell2->row)
        return true;

    return false;
}

status_t ADT_cell_destroy(void **c) {
    cell_t **ct = (cell_t **) c;

    if(ct == NULL)
        return ERROR_NULL_POINTER;

    free(*ct);
    *ct = NULL;

    return OK;
}

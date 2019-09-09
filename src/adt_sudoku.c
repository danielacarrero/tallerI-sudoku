#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "adt_sudoku.h"

status_t ADT_sudoku_init(sudoku_t *sudoku, FILE * fi ) {
    char row_line[LEN_MAX_SUDOKU_LINE];
    char *iter;
    bool eof = false;
    int row = 1;
    int col;

    if (sudoku == NULL || fi == NULL)
        return ERROR_NULL_POINTER;
    if (ADT_vector_create(&(sudoku->initial_cells)) != OK)
        return ERROR_CREATING_SUDOKU;
    if (ADT_vector_create(&(sudoku->current_cells)) != OK)
        return ERROR_CREATING_SUDOKU;

    while(!eof){
        col = 1;
        if (fgets(row_line, LEN_MAX_SUDOKU_LINE, fi) == NULL) {
            eof = true;
        }
        iter = strtok(row_line, DELIMITER_SUDOKU);
        while (iter != NULL && !eof) {
            if (ADT_sudoku_add_initial_cell(sudoku, (uint8_t) row, (uint8_t) col, (uint8_t) atoi(iter)) != OK){
                return ERROR_CREATING_SUDOKU;
            }
            iter = strtok(NULL, DELIMITER_SUDOKU);
            col ++;
        }
        row ++;
    }

    printf("Cargado el sudoku! :)\n");
    return OK;
}

status_t ADT_sudoku_add_initial_cell(sudoku_t * sudoku, uint8_t row, uint8_t col, uint8_t value) {
    cell_t new_cell;
    status_t st;

    if (sudoku == NULL)
        return ERROR_NULL_POINTER;
    if (value == EMPTY_CELL)
        return OK;

    //printf("intentando agregar celda con col: %d, row: %d, value: %d\n", (int)col, (int)row, (int)value);

    new_cell.row = row;
    new_cell.col = col;
    new_cell.value = value;

    if ((st = ADT_vector_append(sudoku->initial_cells, &new_cell)) != OK)
        return st;
    if ((st = ADT_vector_append(sudoku->current_cells, &new_cell)) != OK)
        return st;

    return OK;
}

status_t ADT_sudoku_destroy(sudoku_t *sudoku) {
    status_t st;

    if (sudoku == NULL)
        return ERROR_NULL_POINTER;
    if ((st = ADT_vector_destroy((void *) &(sudoku->initial_cells))) != OK)
        return st;
    if ((st = ADT_vector_destroy((void*) &(sudoku->current_cells))) != OK)
        return st;

    printf("Sudoku destruido!\n");
    return OK;
}

status_t ADT_sudoku_format_printable(const sudoku_t *sudoku, char **printable, size_t size) {
    status_t st;
    size_t row = 1;
    size_t col = 1;
    cell_t search_cell;
    vector_t *search_result;
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
                search_cell.row = (uint8_t) row;
                search_cell.col = (uint8_t) col;

                if ((st = ADT_vector_search(sudoku->current_cells, &search_cell, &search_result)) != OK){
                    printf("error al buscar\n");
                    return st;
                }
                if (search_result->size == 0){
                    strncat(*printable, SUDOKU_EMPTY_CELL, printable_len);
                } else {
                    cell_t *result_cell = (cell_t *) ADT_Vector_element_at(search_result, 0);
                    if (result_cell == NULL){
                        return ERROR_FORMATTING_SUDOKU;
                    }
                    printf("intentando poner el numero: %u\n", (uint8_t) result_cell->value);
                    snprintf(cell_number, LEN_MAX_NUMBER,"%u", (uint8_t) result_cell->value);
                    printf("cell_numbre: %s\n", cell_number);
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

    printf("comparing cells: \n");
    printf("cell 1 row %d col %d value %d\n", (uint8_t) cell1->row, (uint8_t) cell1-> col, (uint8_t) cell1->value);
    printf("cell 2 row %d col %d value %d\n", (uint8_t) cell2->row, (uint8_t) cell2-> col, (uint8_t) cell2->value);

    if ((uint8_t) cell1->col == (uint8_t) cell2->col
        && (uint8_t) cell1->row == (uint8_t) cell2->row)
        return true;

    return false;
}

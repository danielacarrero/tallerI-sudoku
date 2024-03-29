#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "sudoku.h"

static status_t add_initial_cell(sudoku_t * sudoku,
                                size_t row,
                                size_t col,
                                size_t value) {
    cell_t *new_cell;
    cell_t *new_cell2;
    status_t st;

    if (sudoku == NULL)
        return ERROR_NULL_POINTER;
    if (value == EMPTY_CELL)
        return OK;

    new_cell = (cell_t*) malloc(sizeof(cell_t));
    if (new_cell == NULL)
        return ERROR_OUT_OF_MEMORY;

    new_cell2 = (cell_t*) malloc(sizeof(cell_t));
    if (new_cell2 == NULL)
        return ERROR_OUT_OF_MEMORY;

    new_cell->row = row;
    new_cell->col = col;
    new_cell->value = value;
    *new_cell2 = *new_cell;

    st = vector_append(sudoku->initial_cells, new_cell);
    if (st != OK)
        return st;

    st = vector_append(sudoku->current_cells, new_cell2);
    if (st != OK)
        return st;

    return OK;
}

status_t sudoku_init(sudoku_t **sudoku, FILE * fi ) {
    char row_line[LEN_MAX_SUDOKU_LINE];
    char *iter;
    char *temp;
    bool eof = false;
    size_t row = 1;
    size_t col;
    size_t value;
    status_t st;

    if (sudoku == NULL)
        return ERROR_NULL_POINTER;

    *sudoku = (sudoku_t*)malloc(sizeof(sudoku_t));
    if (*sudoku == NULL)
        return ERROR_OUT_OF_MEMORY;
    st = vector_create(&((*sudoku)->initial_cells));
    if (st != OK)
        return ERROR_CREATING_SUDOKU;
    st = vector_create(&((*sudoku)->current_cells));
    if (st != OK)
        return ERROR_CREATING_SUDOKU;

    while (fi != NULL && !eof) {
        col = 1;
        if (fgets(row_line, LEN_MAX_SUDOKU_LINE, fi) == NULL)
            eof = true;
        iter = strtok_r(row_line, DELIMITER_SUDOKU, &temp);
        while (iter != NULL && !eof) {
            value = (size_t) strtol(iter, &temp, 10);
            if (add_initial_cell(*sudoku, row, col, value) != OK){
                return ERROR_CREATING_SUDOKU;
            }
            iter = strtok_r(NULL, DELIMITER_SUDOKU, &temp);
            col ++;
        }
        row ++;
    }

    st = vector_set_destructor((*sudoku)->initial_cells, cell_destroy);
    if (st != OK)
        return st;

    st = vector_set_destructor((*sudoku)->current_cells, cell_destroy);
    if (st != OK)
        return st;

    st = vector_set_copier((*sudoku)->initial_cells, sudoku_copy_cell);
    if (st != OK)
        return st;

    return OK;
}

status_t sudoku_put_value(sudoku_t *sudoku,
                          size_t row,
                          size_t col,
                          size_t val) {
    cell_t *new_cell;
    status_t st = OK;

    if (sudoku == NULL)
        return ERROR_NULL_POINTER;
    if (val == EMPTY_CELL)
        return OK;
    if ((new_cell = (cell_t*)malloc(sizeof(cell_t))) == NULL)
        return ERROR_OUT_OF_MEMORY;

    new_cell->row = row;
    new_cell->col = col;
    new_cell->value = val;

    st = vector_set_searcher(sudoku->initial_cells,
            sudoku_compare_cell_position);
    if (st != OK)
        return st;

    st = vector_set_searcher(sudoku->current_cells,
            sudoku_compare_cell_position);
    if (st != OK)
        return st;

    if (vector_search(sudoku->initial_cells, new_cell) != NULL){
        free(new_cell);
        new_cell = NULL;
        return ERROR_UNMODIFIABLE_CELL;
    }

    if (vector_search(sudoku->current_cells, new_cell) != NULL) {
        st = vector_modify_element(sudoku->current_cells, new_cell);
    } else {
        st = vector_append(sudoku->current_cells, new_cell);
    }

    return st;
}

status_t sudoku_destroy(sudoku_t *sudoku) {
    status_t st;

    if (sudoku == NULL)
        return ERROR_NULL_POINTER;

    st = vector_destroy((void *) &(sudoku->initial_cells));
    if (st != OK)
        return st;

    st = vector_destroy((void *) &(sudoku->current_cells));
    if (st != OK)
        return st;

    free(sudoku);
    sudoku = NULL;

    return OK;
}

status_t sudoku_reset(sudoku_t *sudoku) {
    return vector_copy(sudoku->initial_cells, &(sudoku->current_cells));
}

status_t sudoku_fmt_printable(const sudoku_t *sudoku, char **out, size_t len) {
    size_t row = 1;
    size_t col = 1;
    cell_t search_cell;
    cell_t *result_cell;
    char cell_number[LEN_MAX_NUMBER];

    if (sudoku == NULL || out == NULL)
        return ERROR_NULL_POINTER;

    if (vector_set_searcher(sudoku->current_cells,
            sudoku_compare_cell_position) != OK)
        return ERROR_FORMATTING_SUDOKU;

    strncat(*out, SUDOKU_BIG_CELL_LIMIT_ROW, len);
    len -= strlen(SUDOKU_BIG_CELL_LIMIT_ROW);
    for (size_t t_row = 1; t_row <= SUDOKU_MAX_NUM_TABLE_ROWS; t_row ++) {
        if (t_row % 6 == 0) {
            strncat(*out, SUDOKU_BIG_CELL_LIMIT_ROW, len);
            len -= strlen(SUDOKU_BIG_CELL_LIMIT_ROW);
        } else if (t_row % 2) {
            strncat(*out, SUDOKU_INIT_TABLE_ROW, len);
            len -= strlen(SUDOKU_INIT_TABLE_ROW);
            for (col = 1; col <= MAX_NUM_COLS; col ++) {
                search_cell.row = row;
                search_cell.col = col;

                result_cell = (cell_t *) vector_search(
                        sudoku->current_cells,
                        &search_cell);

                if (result_cell == NULL) {
                    strncat(*out, SUDOKU_EMPTY_CELL, len);
                    len -= strlen(SUDOKU_EMPTY_CELL);
                } else {
                    snprintf(cell_number,
                            LEN_MAX_NUMBER,
                            "%zu",
                            (size_t) result_cell->value);
                    strncat(*out, cell_number, len);
                    len -= strlen(cell_number);
                }

                if (col == MAX_NUM_COLS) {
                    strncat(*out, SUDOKU_FINISH_TABLE_ROW, len);
                    len -= strlen(SUDOKU_FINISH_TABLE_ROW);
                } else if (col % 3 == 0){
                    strncat(*out, SUDOKU_BIG_CELL_LIMIT_COL, len);
                    len -= strlen(SUDOKU_BIG_CELL_LIMIT_COL);
                } else {
                    strncat(*out, SUDOKU_LIMIT_COL, len);
                    len -= strlen(SUDOKU_LIMIT_COL);
                }
            }
            row ++;
        } else {
            strncat(*out, SUDOKU_LIMIT_ROW, len);
            len -= strlen(SUDOKU_LIMIT_ROW);
        }
    }
    return OK;
}

bool sudoku_compare_cell_position(const void *c1, const void *c2) {
    cell_t *cell1 = (cell_t *) c1;
    cell_t *cell2 = (cell_t *) c2;

    if (cell1 == NULL || cell2 == NULL)
        return false;

    if (cell1->col == cell2->col
        && cell1->row == cell2->row)
        return true;

    return false;
}

status_t sudoku_copy_cell(const void *src, void **dst) {
    cell_t *aux_src = (cell_t *) src;
    cell_t *aux_dst;

    if (src == NULL)
        return ERROR_NULL_POINTER;
    aux_dst = (cell_t*) malloc(sizeof(cell_t));
    if (aux_dst == NULL)
        return ERROR_OUT_OF_MEMORY;

    aux_dst->col = aux_src->col;
    aux_dst->row = aux_src->row;
    aux_dst->value = aux_src->value;

    *dst = aux_dst;
    return OK;
}

status_t cell_destroy(void **c) {
    cell_t **ct = (cell_t **) c;

    if (ct == NULL)
        return ERROR_NULL_POINTER;

    free(*ct);
    *ct = NULL;

    return OK;
}

static bool has_repeated_values(size_t arr[], size_t len) {
    for (size_t i = 0; i < len; i++) {
        for (size_t j = i + 1; j < len; j++) {
            if (arr[i] == arr[j]) {
                return true;
            }
        }
    }

    return false;
}

static status_t sudoku_verify_rows(const sudoku_t *sudoku) {
    status_t st;
    cell_t search_cell;
    cell_t *result_cell;
    size_t values_in_row[MAX_NUM_COLS];
    size_t values_in_row_size = 0;

    st = vector_set_searcher(sudoku->current_cells,
            sudoku_compare_cell_position);
    if (st != OK)
        return st;

    for (size_t row = 1; row <= MAX_NUM_ROWS; row++) {
        search_cell.row = row;
        memset(values_in_row, 0, sizeof(values_in_row));
        values_in_row_size = 0;

        for (size_t col = 1; col <= MAX_NUM_COLS; col++) {
            search_cell.col = col;
            result_cell = (cell_t *) vector_search(sudoku->current_cells,
                    &search_cell);
            if (result_cell != NULL) {
                values_in_row[values_in_row_size] = result_cell->value;
                values_in_row_size++;
            }
        }

        if (has_repeated_values(values_in_row, values_in_row_size))
            return ERROR_INVALID_DATA;
    }

    return OK;
}

static status_t sudoku_verify_cols(const sudoku_t *sudoku) {
    status_t st;
    cell_t search_cell;
    cell_t *result_cell;
    size_t values_in_col[MAX_NUM_ROWS];
    size_t values_in_col_size = 0;

    st = vector_set_searcher(sudoku->current_cells,
            sudoku_compare_cell_position);
    if (st != OK)
        return st;

    for (size_t col = 1; col <= MAX_NUM_COLS; col++) {
        search_cell.col = col;
        memset(values_in_col, 0, sizeof(values_in_col));
        values_in_col_size = 0;

        for (size_t row = 1; row <= MAX_NUM_COLS; row++) {
            search_cell.row = row;
            result_cell = (cell_t *) vector_search(sudoku->current_cells,
                    &search_cell);
            if (result_cell != NULL) {
                values_in_col[values_in_col_size] = result_cell->value;
                values_in_col_size++;
            }
        }

        if (has_repeated_values(values_in_col, values_in_col_size))
            return ERROR_INVALID_DATA;
    }

    return OK;
}

static status_t sudoku_verify_big_cells(const sudoku_t *sudoku) {
    status_t st;
    cell_t search_cell;
    cell_t *result_cell;
    size_t values[MAX_NUM_BIG_CELL];
    size_t values_size = 0;
    size_t row;
    size_t col;

    st = vector_set_searcher(sudoku->current_cells,
            sudoku_compare_cell_position);
    if (st != OK)
        return st;

    for (size_t big_cell_row = 1; big_cell_row <= 3; big_cell_row ++) {
        for (size_t big_cell_col = 1; big_cell_col <= 3; big_cell_col ++) {
            memset(values, 0, sizeof(values));
            values_size = 0;
            size_t init_row = (big_cell_row == 1) ? 1 :
                    (big_cell_row - 1) * 3 + 1;
            size_t init_col = (big_cell_col == 1) ? 1 :
                    (big_cell_col - 1) * 3 + 1;
            for (row = init_row; row < init_row + 3 ; row++) {
                for (col = init_col; col < init_col + 3; col++) {
                    search_cell.row = row;
                    search_cell.col = col;
                    result_cell = (cell_t *) vector_search(
                            sudoku->current_cells,
                            &search_cell);
                    if (result_cell != NULL) {
                        values[values_size] = result_cell->value;
                        values_size++;
                    }
                }
            }

            if (has_repeated_values(values, values_size))
                return ERROR_INVALID_DATA;
        }
    }

    return OK;
}

status_t sudoku_verify(const sudoku_t *sudoku) {
    status_t st;

    if ((st = sudoku_verify_rows(sudoku)) != OK) {
        return st;
    }
    if ((st = sudoku_verify_cols(sudoku)) != OK) {
        return st;
    }
    if ((st = sudoku_verify_big_cells(sudoku)) != OK) {
        return st;
    }

    return OK;
}

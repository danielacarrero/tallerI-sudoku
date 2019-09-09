#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "adt_vector.h"


status_t ADT_vector_create(vector_t  **p) {
    if(p == NULL)
        return ERROR_NULL_POINTER;

    if((*p = (vector_t*) malloc(sizeof(vector_t))) == NULL)
        return ERROR_OUT_OF_MEMORY;
    if(((*p) -> elements = (void **)malloc(ADT_VECTOR_INIT_CHOP * sizeof(void*))) == NULL){
        free(*p);
        *p = NULL;
        return ERROR_OUT_OF_MEMORY;
    }
    (*p) -> size = 0;
    (*p) -> searcher = NULL;
    (*p) -> destroyer = NULL;

    return OK;
}

status_t ADT_vector_destroy(void **p) {
    size_t i;
    vector_t **pv = (vector_t **) p;
    status_t st;

    if(pv == NULL)
        return ERROR_NULL_POINTER;

    for(i=0; i < (*pv)->size; i++){
        if((st = (*((*pv) -> destroyer)) ((*pv) -> elements + i)) != OK)
            return st;
        (*pv) -> elements[i] = NULL;
    }
    free((*pv) -> elements);
    free(*pv);
    *pv = NULL;

    return OK;
}

status_t ADT_vector_append(vector_t *p, void *n) {
    void **aux;

    if(p == NULL || n == NULL)
        return ERROR_NULL_POINTER;
    if((aux=(void**)realloc(p -> elements, (p -> size + 1) * sizeof(void *))) == NULL)
        return ERROR_OUT_OF_MEMORY;

    p -> elements = aux;
    p -> elements [p -> size] = n;
    (p -> size)++;

    return OK;
}

status_t ADT_vector_set_searcher(vector_t *p, searcher_t pf) {
    if (p == NULL || pf == NULL)
        return ERROR_NULL_POINTER;

    p -> searcher = pf;

    return OK;
}

/* Search value (v) in vector p1 elements */
void * ADT_vector_search(const vector_t *p1, void *v) {
    if (p1 == NULL || p1->searcher == NULL || v == NULL)
        return NULL;

    for (size_t i = 0; i < p1->size; i++) {
        if ((*(p1->searcher))((void *)p1->elements[i], v) == true) {
            printf("in search, appending element: %zu\n", i);
            return p1->elements[i];
        }
    }

    return NULL;
}

void * ADT_Vector_element_at(const vector_t *p, size_t pos) {
    if (p == NULL)
        return NULL;
    if (pos > p->size)
        return NULL;
    return p->elements[pos];
}

status_t ADT_Vector_set_destructor(vector_t *p, destroyer_t pf) {
    if(p == NULL || pf == NULL)
        return ERROR_NULL_POINTER;

    p -> destroyer = pf;

    return OK;
}

#ifndef VECTOR__H
#define VECTOR__H

#include "types.h"

#define ADT_VECTOR_INIT_CHOP 1

typedef bool (*searcher_t)(const void *element, const void *value);

typedef struct vector{
    void **elements;
    size_t size;
    searcher_t searcher;
} vector_t;

status_t ADT_vector_create(vector_t  **p);
status_t ADT_vector_destroy(void **p);
status_t ADT_vector_append(vector_t *p, void *n);
status_t ADT_vector_set_searcher(vector_t *p, searcher_t pf);
void * ADT_vector_search(const vector_t *p1, void *v);
void * ADT_Vector_element_at(const vector_t *p, size_t pos);

#endif

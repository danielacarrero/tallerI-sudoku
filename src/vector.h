#ifndef VECTOR__H
#define VECTOR__H

#include "types.h"

#define VECTOR_INIT_CHOP 1

typedef bool (*searcher_t)(const void *element, const void *value);
typedef status_t (*destroyer_t)(void **);
typedef status_t (*copier_t)(const void *src, void **dest);

typedef struct vector{
    void **elements;
    size_t size;
    searcher_t searcher;
    destroyer_t destroyer;
    copier_t copier;
} vector_t;

status_t vector_create(vector_t  **p);
status_t vector_destroy(void **p);
status_t vector_append(vector_t *p, void *n);
status_t vector_set_searcher(vector_t *p, searcher_t pf);
status_t vector_set_destructor(vector_t *p, destroyer_t pf);
void * vector_search(const vector_t *p1, void *v);
void * vector_element_at(const vector_t *p, size_t pos);
status_t vector_copy(const vector_t *src, vector_t **dest);
status_t vector_set_copier(vector_t *p, copier_t pf);
status_t vector_modify_element(vector_t *p1, void *v);
status_t vector_remove_element(vector_t *p1, void *v);

#endif

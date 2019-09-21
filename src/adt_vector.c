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
    (*p) -> copier = NULL;

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
        if ((*(p1->searcher))(p1->elements[i], v) == true) {
            return p1->elements[i];
        }
    }

    return NULL;
}

void * ADT_vector_element_at(const vector_t *p, size_t pos) {
    if (p == NULL)
        return NULL;
    if (pos > p->size)
        return NULL;
    return p->elements[pos];
}

status_t ADT_vector_remove_element(vector_t *p1, void *v) {
    vector_t *aux;
    void * element = NULL;
    status_t st;

    if (p1 == NULL || p1->searcher == NULL || v == NULL)
        return ERROR_NULL_POINTER;

    for (size_t i = 0; i < p1->size; i++) {
        if ((*(p1->searcher))(p1->elements[i], v) == true) {
            element = p1->elements[i];
        }
    }

    if (element == NULL) {
        return ERROR_NOT_FOUND;
    }

    if((st = ADT_vector_create(&aux)) != OK)
        return st;

    for (size_t i = 0; i < p1->size; i++) {
        if (p1->elements[i] != element) {
            if((st = ADT_vector_append(aux, p1->elements[i])) != OK) {
                ADT_vector_destroy((void **) &aux);
                return st;
            }
        }
    }

    if((st = ADT_vector_destroy((void **) &p1)) != OK) {
        ADT_vector_destroy((void **) &aux);
        return st;
    }

    p1 = aux;
    return OK;
}

status_t ADT_vector_modify_element(vector_t *p1, void *v) {
    status_t st;
    if(p1 == NULL || p1->searcher == NULL
        || v == NULL || p1->destroyer == NULL)
        return ERROR_NULL_POINTER;

    for (size_t i = 0; i < p1->size; i++) {
        if ((*(p1->searcher))(p1->elements[i], v) == true) {
            if((st = (*(p1->destroyer)) (p1->elements + i)) != OK)
                return st;
            p1->elements[i] = v;
        }
    }

    return OK;
}

status_t ADT_vector_set_destructor(vector_t *p, destroyer_t pf) {
    if(p == NULL || pf == NULL)
        return ERROR_NULL_POINTER;

    p->destroyer = pf;

    return OK;
}

status_t ADT_vector_set_copier(vector_t *p, copier_t pf) {
    if (p == NULL || pf == NULL)
        return ERROR_NULL_POINTER;

    p->copier = pf;

    return OK;
}

status_t ADT_vector_copy(const vector_t *src, vector_t **dest) {
    status_t st;
    void **aux;

    if (src == NULL || dest == NULL || src->copier == NULL)
        return ERROR_NULL_POINTER;

    if ((st = ADT_vector_destroy((void**) dest)) != OK){
        return st;
    }
    if ((st = ADT_vector_create(dest)) != OK) {
        return st;
    }

    if((aux = (void **)malloc(sizeof(void *))) == NULL)
        return ERROR_OUT_OF_MEMORY;

    for (size_t i = 0; i < src->size; i++) {
        if((st = (*(src->copier))(src->elements[i], aux)) != OK) {
            return st;
        }
        ADT_vector_append(*dest, *aux);
    }

    (*dest)->destroyer = src->destroyer;
    (*dest)->copier = src->copier;
    (*dest)->searcher = src->searcher;

    free(aux);
    aux = NULL;

    return OK;
}

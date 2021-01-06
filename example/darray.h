
#ifndef DARRAY_H
#define DARRAY_H

#include <stdlib.h>

struct darray;
typedef struct darray *darray;

darray darray_create(void);
void darray_set_cleanup(darray da, void (*cleanup_proc)(void *));
int darray_insert_elem(darray *da, void *elem, size_t index);
void darray_set_elem(darray da, void *elem, size_t index);
void darray_remove_elem(darray da, size_t index);
void *darray_get_elem(darray da, size_t index);
size_t darray_get_len(darray da);
int darray_append(darray *da, void *elem);
void darray_swap(darray da, size_t i, size_t j);
void darray_destroy(darray *da);

#endif

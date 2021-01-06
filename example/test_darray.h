
#ifndef TEST_DARRAY_H
#define TEST_DARRAY_H

#include <stdbool.h>

bool test_darray_create(void);
bool test_darray_set_cleanup(void);
bool test_darray_insert_get_elem(void);
bool test_darray_set_elem(void);
bool test_darray_remove_elem(void);
bool test_darray_get_len(void);
bool test_darray_append(void);
bool test_darray_swap(void);
bool test_darray_destroy(void);
bool test_darray_memory_cleanup(void);
bool test_darray_stress(void);

#endif


#include "test_utils.h"
#include "test_darray.h"

static const struct test_entry entries[] = {
	test_entry(test_darray_create),
	test_entry(test_darray_set_cleanup),
	test_entry(test_darray_insert_get_elem),
	test_entry(test_darray_set_elem),
	test_entry(test_darray_remove_elem),
	test_entry(test_darray_get_len),
	test_entry(test_darray_append),
	test_entry(test_darray_swap),
	test_entry(test_darray_destroy),
	test_entry(test_darray_memory_cleanup),
	test_entry(test_darray_stress),
	null_entry
};

int main(void)
{
	return test_main(entries);
}


#include <stdlib.h>

#include "darray.h"
#include "test_darray.h"
#include "test_utils.h"

bool test_darray_create(void)
{
	darray d;
	bool test_1 = !is_assert_invoked(d = darray_create());
	darray_destroy(&d);

	return test_1;
}

int test_cleanup_counter;
static void test_cleanup(void *vp)
{
	test_cleanup_counter++;
}

bool test_darray_set_cleanup(void)
{
	darray d = darray_create();
	bool test_1 = !is_assert_invoked(darray_set_cleanup(d, &test_cleanup));
	darray_destroy(&d);

	return test_1;
}

bool test_darray_insert_get_elem(void)
{
	bool test_1 = is_assert_invoked(darray_insert_elem(NULL, NULL, 1));

	int x = 1;
	int y = 2;
	int z = 3;

	darray d = darray_create();
	
	bool test_2 = is_assert_invoked(darray_insert_elem(&d, &x, 1));

	darray_insert_elem(&d, &x, 0);
	darray_insert_elem(&d, &y, 1);
	darray_insert_elem(&d, &z, 2);

	bool test_3 = *(int *)darray_get_elem(d, 0) == 1;
	bool test_4 = *(int *)darray_get_elem(d, 1) == 2;
	bool test_5 = *(int *)darray_get_elem(d, 2) == 3;

	darray_destroy(&d);

	return test_1 && test_2 && test_3 && test_4 && test_5;
}

bool test_darray_set_elem(void)
{
	bool test_1 = is_assert_invoked(darray_set_elem(NULL, NULL, 1));

	darray d = darray_create();
	int x = 1;
	int y = 2;
	int z = 3;

	darray_insert_elem(&d, &x, 0);
	darray_insert_elem(&d, &y, 1);
	darray_insert_elem(&d, &z, 2);

	bool test_2 = *(int *)darray_get_elem(d, 0) == 1;
	bool test_3 = *(int *)darray_get_elem(d, 1) == 2;
	bool test_4 = *(int *)darray_get_elem(d, 2) == 3;
	
	darray_set_elem(d, &z, 0);
	darray_set_elem(d, &y, 1);
	darray_set_elem(d, &x, 2);

	bool test_5 = *(int *)darray_get_elem(d, 0) == 3;
	bool test_6 = *(int *)darray_get_elem(d, 1) == 2;
	bool test_7 = *(int *)darray_get_elem(d, 2) == 1;

	darray_destroy(&d);

	return test_1 && test_2 && test_3 && test_4 && test_5 && test_6 && test_7;
}

bool test_darray_remove_elem(void)
{
	darray d = darray_create();
	int x = 1;
	int y = 2;
	int z = 3;

	darray_insert_elem(&d, &x, 0);
	darray_insert_elem(&d, &y, 1);
	darray_insert_elem(&d, &z, 2);

	bool test_1 = *(int *)darray_get_elem(d, 0) == 1;
	bool test_2 = *(int *)darray_get_elem(d, 1) == 2;
 	bool test_3 = *(int *)darray_get_elem(d, 2) == 3;

	darray_remove_elem(d, 0);
	bool test_4 = *(int *)darray_get_elem(d, 0) == 2;
	bool test_5 = *(int *)darray_get_elem(d, 1) == 3;

	darray_destroy(&d);

	return test_1 && test_2 && test_3 && test_4 && test_5;
}

bool test_darray_get_len(void)
{
	darray d = darray_create();
	int x = 1;
	int y = 2;
	int z = 3;	

	bool test_1 = is_assert_invoked(darray_get_len(NULL));
	bool test_2 = darray_get_len(d) == 0;

	darray_append(&d, &x);
	darray_append(&d, &y);
	darray_append(&d, &z);

	bool test_3 = darray_get_len(d) == 3;

	darray_remove_elem(d, 0);

	bool test_4 = darray_get_len(d) == 2;
	
	darray_destroy(&d);

	return test_1 && test_2 && test_3 && test_4;
}

bool test_darray_append(void)
{
	darray d = darray_create();
	int x = 1;
	int y = 2;
	int z = 3;

	darray_append(&d, &x);
	darray_append(&d, &y);
	darray_append(&d, &z);

	bool test_1 = *(int *)darray_get_elem(d, 0) == 1;
	bool test_2 = *(int *)darray_get_elem(d, 1) == 2;
	bool test_3 = *(int *)darray_get_elem(d, 2) == 3;

	darray_destroy(&d);

	return test_1 && test_2 && test_3;
}

bool test_darray_swap(void)
{
	darray d = darray_create();
	int x = 1;
	int y = 2;
	int z = 3;

	darray_append(&d, &x);
	darray_append(&d, &y);
	darray_append(&d, &z);

	darray_swap(d, 0, 1);

	bool test_1 = *(int *)darray_get_elem(d, 0) == 2;
	bool test_2 = *(int *)darray_get_elem(d, 1) == 1;
	bool test_3 = *(int *)darray_get_elem(d, 2) == 3;

	darray_swap(d, 2, 0);

	bool test_4 = *(int *)darray_get_elem(d, 0) == 3;
	bool test_5 = *(int *)darray_get_elem(d, 1) == 1;
	bool test_6 = *(int *)darray_get_elem(d, 2) == 2;

	darray_destroy(&d);

	return test_1 && test_2 && test_3 && test_4 && test_5 && test_6;
}

bool test_darray_destroy(void)
{
	bool test_1 = is_assert_invoked(darray_destroy(NULL));
	darray d = darray_create();
	darray_set_cleanup(d, &test_cleanup);
	int x = 1;
	int y = 2;
	int z = 3;

	darray_append(&d, &x);
	darray_append(&d, &y);
	darray_append(&d, &z);

	test_cleanup_counter = 0;
	darray_destroy(&d);
	bool test_2 = test_cleanup_counter == 3;
	
	return test_1 && test_2;
}

bool test_darray_memory_cleanup(void)
{
	size_t n = current_number_of_allocations();

	darray d = darray_create();
	darray_set_cleanup(d, &free);
	for (int i = 0; i < 10; i++) {
		darray_append(&d, malloc(1));
	}
	darray_destroy(&d);

	bool test_1 = current_number_of_allocations() == n;

	return test_1;
}

bool test_darray_stress(void)
{
	srand(100);

	int test = 42;
	const size_t length = 1000;
	size_t length_copy = length;
	darray d = darray_create();

	bool test_1 = darray_get_len(d) == 0;
	
	for (int i = 0; i < length; i++) {
		darray_append(&d, &test);
	}

	bool test_2 = darray_get_len(d) == length;

	bool test_3 = true;
	bool test_4 = true;
	for (int i = 0; i < length; i++) {
		size_t index = length_copy * rand() / (double)RAND_MAX;	
		test_3 = test_3 && !is_assert_invoked(darray_remove_elem(d, index));
		test_4 = test_4 && (darray_get_len(d) == --length_copy);
	}

	bool test_5 = darray_get_len(d) == 0;
	darray_destroy(&d);

	return test_1 && test_2 && test_3 && test_4 && test_5;
}


#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "darray.h"
#include "test_utils.h"

static const size_t initial_size = 8;
static const size_t scaling_factor = 2;

struct darray {
	size_t len;
	size_t size;
	void (*cleanup)(void *);
	void *buffer[];
};

darray darray_create(void)
{
	struct darray *result = malloc((sizeof *result) + sizeof (void *) * initial_size);
	result->len = 0;
	result->size = initial_size;
	result->cleanup = NULL;
	memset(result->buffer, 0, (sizeof (void *)) * initial_size);

	assert(result->len == 0);
	assert(result->size == initial_size);
	assert(result->cleanup == NULL);
	for (int i = 0; i < result->size; i++) {
		assert(!result->buffer[i]);
	}

	return result;
}

void darray_set_cleanup(darray da, void (*cleanup_proc)(void *))
{
	assert(da);
	assert(cleanup_proc);

	da->cleanup = cleanup_proc;

	assert(da->cleanup == cleanup_proc);
}

static int darray_incr_size(darray *da)
{
	assert(da);
	assert(*da);
	
	*da = realloc(*da, (sizeof **da) + ((*da)->size *= scaling_factor) * sizeof (void *));
	if (!(*da)) {
		return 1;
	}

	assert(*da);
	return 0;
}

void darray_swap(darray da, size_t i, size_t j)
{
	assert(da);
	assert(i < da->len);
	assert(j < da->len);

	void *temp = da->buffer[i];
	da->buffer[i] = da->buffer[j];
	da->buffer[j] = temp;
}

void darray_set_elem(darray da, void *elem, size_t index)
{
	assert(da);
	assert(index < da->len);

	da->buffer[index] = elem;
}

int darray_insert_elem(darray *da, void *elem, size_t index)
{
	assert(da);
	assert(*da);
	assert(index <= (*da)->len);

	/* allocate more memory if needed */
	if ((*da)->len == (*da)->size) {
		int error_code = darray_incr_size(da);
		if (error_code) {
			return error_code;
		}
	}

	/* append the element, and swap until it is in the correct location */
	(*da)->buffer[(*da)->len] = elem;
	for (size_t i = (*da)->len; i > index; i--) {
		darray_swap(*da, i, i - 1);
	}
	(*da)->len++;

	assert((*da)->buffer[index] == elem);
	return 0;
}

void darray_remove_elem(darray da, size_t index)
{
	assert(da);
	assert(index < da->len);

	if (da->cleanup)
		da->cleanup(da->buffer[index]);
	
	da->buffer[index] = NULL;

	for (size_t i = index; i < da->len - 1; i++) {
		darray_swap(da, i, i + 1);
	}

	da->len--;
	assert(!da->buffer[da->len + 1]);
}

void *darray_get_elem(darray da, size_t index)
{
	assert(da);
	assert(index < da->len);
	return da->buffer[index];
}

size_t darray_get_len(darray da)
{
	assert(da);
	return da->len;
}

int darray_append(darray *da, void *elem)
{
	assert(da);
	darray_insert_elem(da, elem, (*da)->len);
	assert((*da)->buffer[(*da)->len - 1] == elem);
}

void darray_destroy(darray *da)
{
	assert(da);
	assert(*da);

	if ((*da)->cleanup) {
		for (int i = 0; i < (*da)->len; i++) {
			(*da)->cleanup((*da)->buffer[i]);
		}
	}
	
	free(*da);
	*da = NULL;
}

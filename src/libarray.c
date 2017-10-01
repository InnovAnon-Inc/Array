#if HAVE_CONFIG_H
#include <config.h>
#endif

#define _POSIX_C_SOURCE 200112L
#define __STDC_VERSION__ 200112L

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <mmalloc.h>
#include <swap.h>

#include <array.h>

__attribute__ ((const, leaf, nothrow, warn_unused_result))
size_t datasz (size_t esz, size_t n) { return esz * n; }

__attribute__ ((const, nothrow, warn_unused_result))
size_t arraysz (size_t esz, size_t n) {
	return sizeof (array_t);
}

__attribute__ ((alloc_align (1), alloc_size (1, 2), /*malloc,*/
	nothrow, warn_unused_result))
array_t *ez_alloc_array (size_t esz, size_t n) {
	void *restrict combined[2];
	size_t eszs[2];
	array_t *restrict array;

	eszs[0] = arraysz (esz, n);
	eszs[1] = datasz  (esz, n);
	error_check (mmalloc (combined, eszs,
		eszs[0] + eszs[1], ARRSZ (eszs)) != 0)
		return NULL;
	array       = (array_t *restrict) combined[0];
	array->data = (void *restrict)    combined[1];

	return array;
}

__attribute__ ((leaf, nonnull (1), nothrow))
void ez_free_array (array_t *restrict array) {
	free_array (array);
	mfree (array);
}

NOTE (this would be way faster if esz were static
	i.e. this is the cost of this style of generics)
__attribute__ ((leaf, nonnull (1), nothrow, pure, returns_nonnull, warn_unused_result))
void *index_array (array_t const *restrict array, size_t i) {
	char *restrict data;
	char *restrict ret;
	assert (i < array->n);
	data = (char *restrict) array->data;
	ret  = data + i * array->esz;
	return (void *restrict) ret;
}

__attribute__ ((leaf, nonnull (1, 2), nothrow))
void init_array (array_t *restrict array,
	void *restrict data, size_t esz, size_t n) {
	array->data = data;
	array->esz  = esz;
	array->n    = n;
}

__attribute__ ((nonnull (1), nothrow, warn_unused_result))
int alloc_array (array_t *restrict array,
	size_t esz, size_t n) {
	void *restrict data;
	data = malloc (esz * n);
	error_check (data == NULL) return -1;
	init_array (array, data, esz, n);
	return 0;
}

__attribute__ ((nonnull (1), nothrow, warn_unused_result))
int realloc_array (array_t *restrict array, size_t n) {
	void *restrict new_data;
	assert (n != 0);
	new_data = realloc (array->data, array->esz * n);
	error_check (new_data == NULL) return -1;
	array->data = new_data;
	array->n = n;
	return 0;
}

__attribute__ ((nonnull (1, 3), nothrow))
void get_array (array_t const *restrict array, size_t i,
	void *restrict e) {
	void const *restrict src = index_array (array, i);
	(void) memcpy (e, src, array->esz);
	assert (memcmp (src, e, array->esz) == 0);
}

__attribute__ ((nonnull (1, 3), nothrow))
void gets_array (array_t const *restrict array, size_t i,
	void *restrict e, size_t n) {
	void const *restrict src;
	assert (i + n < array->n);
	src = index_array (array, i);
	(void) memcpy (e, src, array->esz * n);
	TODO (verify that data is correctly copied)
}

__attribute__ ((nonnull (1, 3), nothrow))
void set_array (array_t const *restrict array, size_t i,
	void const *restrict e) {
	void *restrict dest = index_array (array, i);
	(void) memcpy (dest, e, array->esz);
	assert (memcmp (dest, e, array->esz) == 0);
}

__attribute__ ((nonnull (1, 3), nothrow))
void sets_array (array_t const *restrict array, size_t i,
	void const *restrict e, size_t n) {
	void *restrict dest;
	assert (i + n < array->n);
	dest = index_array (array, i);
	(void) memcpy (dest, e, array->esz * n);
	TODO (verify that data is correctly copied)
}

__attribute__ ((nonnull (1), nothrow))
void cp_array (array_t const *restrict array, size_t i, size_t j) {
	void const *restrict src  = index_array (array, i);
	void *restrict dest = index_array (array, j);
	memcpy (dest, src, array->esz);
	assert (memcmp (src, dest, array->esz) == 0);
}

/* src and dest should not overlap */
__attribute__ ((nonnull (1), nothrow))
void cps_array (array_t const *restrict array,
	size_t i, size_t j, size_t n) {
	void const *restrict src;
	void *restrict dest;
	assert (i + n < array->n);
	assert (j + n < array->n);
	assert (i + n < j || j + n < i);
	src  = index_array (array, i);
	dest = index_array (array, j);
	memcpy (dest, src, array->esz * n);
	TODO (verify that data is correctly copied)
}

__attribute__ ((nonnull (1), nothrow))
void mvs_array (array_t const *restrict array,
	size_t i, size_t j, size_t n) {
	void const *src;
	void *dest;
	assert (i + n < array->n);
	assert (j + n < array->n);
	src  = index_array (array, i);
	dest = index_array (array, j);
	memmove (dest, src, array->esz * n);
	TODO (verify that data is correctly copied)
}

__attribute__ ((nonnull (1, 4), nothrow))
void swap_array (array_t const *restrict array,
	size_t i, size_t j, void *restrict tmp) {
	void *restrict src  = index_array (array, i);
	void *restrict dest = index_array (array, j);
	swap (src, dest, tmp, array->esz);
	TODO (verify that data is correctly copied)
}

__attribute__ ((nonnull (1, 5), nothrow))
void swaps_array (array_t const *restrict array,
	size_t i, size_t j, size_t n, void *restrict tmp) {
	void *restrict src;
	void *restrict dest;
	assert (i + n < array->n);
	assert (j + n < array->n);
	src  = index_array (array, i);
	dest = index_array (array, j);
	swaps (src, dest, tmp, array->esz, n);
	TODO (verify that data is correctly copied)
}

/* src and dest should not overlap ? */
__attribute__ ((nonnull (1), nothrow))
void swap_array2 (array_t const *restrict array,
	size_t i, size_t j) {
	void *restrict src  = index_array (array, i);
	void *restrict dest = index_array (array, j);
	swap2 (src, dest, array->esz);
	TODO (verify that data is correctly copied)
}

/* src and dest should not overlap ? */
__attribute__ ((nonnull (1), nothrow))
void swaps_array2 (array_t const *restrict array,
	size_t i, size_t j, size_t n) {
	void *restrict src  = index_array (array, i);
	void *restrict dest = index_array (array, j);
	swaps2 (src, dest, array->esz, n);
	TODO (verify that data is correctly copied)
}

__attribute__ ((leaf, nonnull (1), nothrow))
void free_array (array_t const *restrict array) {
	free (array->data);
}

__attribute__ ((leaf, nonnull (1, 2), nothrow, pure, warn_unused_result))
size_t indexOf_array (array_t const *restrict array,
	void const *restrict e) {
	size_t i;
	void *restrict tmp;
	TODO (is this pragma ok ?)
	#pragma GCC ivdep
	for (i = 0; i != array->n; i++) {
		tmp = index_array (array, i);
		if (memcmp (tmp, e, array->esz) == 0)
			return i;
	}
	assert (false);
	__builtin_unreachable ();
}

__attribute__ ((leaf, nonnull (1, 2), nothrow, pure, warn_unused_result))
bool contains_array (array_t const *restrict array,
	void const *restrict e) {
	size_t i;
	void *restrict tmp;
	TODO (is this pragma ok ?)
	#pragma GCC ivdep
	for (i = 0; i != array->n; i++) {
		tmp = index_array (array, i);
		if (memcmp (tmp, e, array->esz) == 0)
			return true;
	}
	return false;
}

__attribute__ ((nonnull (1, 2), nothrow, pure, warn_unused_result))
ssize_t indexOf_array_chk (array_t const *restrict array,
	void const *restrict e) {
	size_t i;
	void *restrict tmp;
	TODO (is this pragma ok ?)
	#pragma GCC ivdep
	for (i = 0; i != array->n; i++) {
		tmp = index_array (array, i);
		if (memcmp (tmp, e, array->esz) == 0)
			return (ssize_t) i;
	}
	return (ssize_t) -1;
}

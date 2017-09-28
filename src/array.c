#if HAVE_CONFIG_H
#include <config.h>
#endif

#define _POSIX_C_SOURCE 200112L
#define __STDC_VERSION__ 200112L

/*#define NDEBUG 1*/

#ifndef NDEBUG
#include <stdio.h>
#endif
#include <stdlib.h>
#include <string.h>

/*#include <math.h>*/

#include <array.h>

__attribute__ ((leaf, nonnull (1), pure, returns_nonnull, warn_unused_result))
void *index_array (array_t const *restrict array, size_t i) {
	char *restrict data = (char *restrict) array->data;
	char *restrict ret  = data + i * array->esz;
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
	void *restrict new_data = realloc (array->data, array->esz * n);
	error_check (new_data == NULL) return -1;
	array->data = new_data;
	array->n = n;
	return 0;
}

__attribute__ ((nonnull (1, 3), nothrow))
void get_array (array_t const *restrict array, size_t i,
	void *restrict e) {
	void *restrict src = index_array (array, i);
	(void) memcpy (e, src, array->esz);
}

__attribute__ ((nonnull (1, 3), nothrow))
void gets_array (array_t const *restrict array, size_t i,
	void *restrict e, size_t n) {
	void *restrict src = index_array (array, i);
	(void) memcpy (e, src, array->esz * n);
}

__attribute__ ((nonnull (1, 3), nothrow))
void set_array (array_t const *restrict array, size_t i,
	void const *restrict e) {
	void *restrict dest = index_array (array, i);
	(void) memcpy (dest, e, array->esz);
}

__attribute__ ((nonnull (1, 3), nothrow))
void sets_array (array_t const *restrict array, size_t i,
	void const *restrict e, size_t n) {
	void *restrict dest = index_array (array, i);
	(void) memcpy (dest, e, array->esz * n);
}

__attribute__ ((nonnull (1), nothrow))
void cp_array (array_t const *restrict array, size_t i, size_t j) {
	void *restrict src  = index_array (array, i);
	void *restrict dest = index_array (array, j);
	memcpy (dest, src, array->esz);
}

/* src and dest should not overlap */
__attribute__ ((nonnull (1), nothrow))
void cps_array (array_t const *restrict array,
	size_t i, size_t j, size_t n) {
	void *restrict src  = index_array (array, i);
	void *restrict dest = index_array (array, j);
	memcpy (dest, src, array->esz * n);
}

__attribute__ ((nonnull (1), nothrow))
void mvs_array (array_t const *restrict array,
	size_t i, size_t j, size_t n) {
	void *src  = index_array (array, i);
	void *dest = index_array (array, j);
	memmove (dest, src, array->esz * n);
}

__attribute__ ((nonnull (1, 4), nothrow))
void swap_array (array_t const *restrict array,
	size_t i, size_t j, void *restrict tmp) {
	void *restrict src  = index_array (array, i);
	void *restrict dest = index_array (array, j);
	swap (src, dest, tmp, array->esz);
}

__attribute__ ((nonnull (1, 5), nothrow))
void swaps_array (array_t const *restrict array,
	size_t i, size_t j, size_t n, void *restrict tmp) {
	void *restrict src  = index_array (array, i);
	void *restrict dest = index_array (array, j);
	swaps (src, dest, tmp, array->esz, n);
}

/* src and dest should not overlap ? */
__attribute__ ((nonnull (1), nothrow))
void swap_array2 (array_t const *restrict array,
	size_t i, size_t j) {
	void *restrict src  = index_array (array, i);
	void *restrict dest = index_array (array, j);
	swap2 (src, dest, array->esz);
}

/* src and dest should not overlap ? */
__attribute__ ((nonnull (1), nothrow))
void swaps_array2 (array_t const *restrict array,
	size_t i, size_t j, size_t n) {
	void *restrict src  = index_array (array, i);
	void *restrict dest = index_array (array, j);
	swaps2 (src, dest, array->esz, n);
}

__attribute__ ((leaf, nonnull (1), nothrow))
void free_array (array_t const *restrict array) {
	free (array->data);
}

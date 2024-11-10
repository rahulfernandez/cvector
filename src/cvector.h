/* vim: set noet ts=2 sts=2 sw=2: */
/* SPDX-License-Identifier: BSD-2-Clause */
/* Copyright © 2024 David Llewellyn-Jones */

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

// The type
#define Vector(TYPE) Vector_##TYPE

// The methods
#define vector_construct(TYPE) vector_construct_##TYPE
#define vector_new(TYPE) vector_new_##TYPE
#define vector_destruct(TYPE) vector_destruct_##TYPE
#define vector_delete(TYPE) vector_delete_##TYPE
#define vector_get(TYPE) vector_get_##TYPE
#define vector_resize(TYPE) vector_resize_##TYPE
#define vector_push(TYPE) vector_push_##TYPE
#define vector_pop(TYPE) vector_pop_##TYPE
#define vector_length(TYPE) vector_length_##TYPE
#define vector_debug_print_space(TYPE) vector_debug_print_space_##TYPE

// Used by the implementation
#define VECTOR_SPACE_STRIDE (8)

// The implementation
#define VECTOR_TEMPLATE(TYPE) \
typedef struct _Vector_##TYPE { \
	uint64_t space; \
	uint64_t count; \
 \
	TYPE *array; \
} Vector_##TYPE; \
 \
void vector_construct_##TYPE(Vector_##TYPE *data) { \
	if (data) { \
		data->space = VECTOR_SPACE_STRIDE; \
		data->count = 0; \
		data->array = calloc(sizeof(TYPE), VECTOR_SPACE_STRIDE); \
	} \
} \
 \
Vector_##TYPE *vector_new_##TYPE() { \
	Vector_##TYPE *data; \
 \
	data = calloc(sizeof(Vector_##TYPE), 1); \
	vector_construct_##TYPE(data); \
 \
	return data; \
} \
 \
void vector_destruct_##TYPE(Vector_##TYPE * data) { \
	uint64_t pos; \
 \
	if (data->array) { \
		for (pos = 0; pos < data->count; ++pos) { \
			TYPE##_destruct(&data->array[pos]); \
		} \
 \
		free(data->array); \
		data->array = NULL; \
	} \
	data->space = 0; \
	data->count = 0; \
} \
 \
Vector_##TYPE *vector_delete_##TYPE(Vector_##TYPE *data) { \
	if (data) { \
		vector_destruct_##TYPE(data); \
 \
		free(data); \
	} \
	return NULL; \
} \
 \
TYPE vector_get_##TYPE(Vector_##TYPE *data, uint64_t position) { \
	return data->array[position]; \
} \
 \
void vector_resize_##TYPE(Vector_##TYPE *data, uint64_t required) { \
	uint64_t quantised; \
 \
	quantised = required + VECTOR_SPACE_STRIDE - (required % VECTOR_SPACE_STRIDE); \
 \
	if (quantised != data->space) { \
		printf("Resizing vector to to: %lu items\n", quantised); \
 \
		data->array = realloc(data->array, sizeof(TYPE) * quantised); \
		assert(data->array != NULL); \
		data->space = quantised; \
	} \
} \
 \
void vector_push_##TYPE(Vector_##TYPE *data, TYPE item) { \
	uint64_t space_required = data->count + 1; \
	uint64_t count; \
 \
	count = data->count + 1; \
	vector_resize_##TYPE(data, count); \
	memcpy(&data->array[count - 1], &item, sizeof(TYPE)); \
	data->count = count; \
} \
 \
TYPE vector_pop_##TYPE(Vector_##TYPE *data) { \
	TYPE result; \
 \
	if (data->count > 0) { \
		data->count -= 1; \
		memcpy(&result, &data->array[data->count], sizeof(TYPE)); \
 \
		vector_resize_##TYPE(data, data->count); \
	} \
	else { \
		TYPE##_construct(&result); \
	} \
 \
	return result; \
} \
 \
uint64_t vector_length_##TYPE(Vector_##TYPE *data) { \
	return data->count; \
} \
 \
void vector_debug_print_space_##TYPE(Vector_##TYPE *data) { \
	printf("Vector count: %lu\n", data->count); \
	printf("Vector allocation: %lu\n", data->space); \
}


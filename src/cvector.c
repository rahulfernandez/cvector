/* vim: set noet ts=2 sts=2 sw=2: */
/* SPDX-License-Identifier: BSD-2-Clause */
/* Copyright © 2024 David Llewellyn-Jones */

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "example-class.h"

#include "cvector.h"

#define VECTOR_SPACE_STRIDE (8)

struct _Vector {
	uint64_t space;
	uint64_t count;

	Example *array;
};

void vector_construct(Vector *data) {
	if (data) {
		data->space = VECTOR_SPACE_STRIDE;
		data->count = 0;
		data->array = calloc(sizeof(Example), VECTOR_SPACE_STRIDE);
	}
}

Vector *vector_new() {
	Vector *data;
	
	data = calloc(sizeof(Vector), 1);
	vector_construct(data);

	return data;
}

void vector_destruct(Vector * data) {
	uint64_t pos;

	if (data->array) {
		for (pos = 0; pos < data->count; ++pos) {
			example_destruct(&data->array[pos]);
		}

		free(data->array);
		data->array = NULL;
	}
	data->space = 0;
	data->count = 0;
}

Vector *vector_delete(Vector *data) {
	if (data) {
		vector_destruct(data);

		free(data);
	}
	return NULL;
}

Example vector_get(Vector *data, uint64_t position) {
	return data->array[position];
}

void vector_resize(Vector *data, uint64_t required) {
	uint64_t quantised;

	quantised = required + VECTOR_SPACE_STRIDE - (required % VECTOR_SPACE_STRIDE);

	if (quantised != data->space) {
		printf("Resizing vector to to: %lu items\n", quantised);

		data->array = realloc(data->array, sizeof(Example) * quantised);
		assert(data->array != NULL);
		data->space = quantised;
	}
}

void vector_push(Vector *data, Example example) {
	uint64_t space_required = data->count + 1;
	uint64_t count;

	count = data->count + 1;
	vector_resize(data, count);
	memcpy(&data->array[count - 1], &example, sizeof(Example));
	data->count = count;
}

Example vector_pop(Vector *data) {
	Example result;
	
	example_construct(&result);
	if (data->count > 0) {
		data->count -= 1;
		memcpy(&result, &data->array[data->count], sizeof(Example));

		vector_resize(data, data->count);
	}
	
	return result;
}

uint64_t vector_length(Vector *data) {
	return data->count;
}

void vector_debug_print_space(Vector *data) {
	printf("Vector count: %lu\n", data->count);
	printf("Vector allocation: %lu\n", data->space);
}


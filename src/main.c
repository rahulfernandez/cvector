/* vim: set noet ts=2 sts=2 sw=2: */
/* SPDX-License-Identifier: BSD-2-Clause */
/* Copyright © 2024 David Llewellyn-Jones */

#include <stdio.h>

#include "example-class.h"
#include "cvector.h"

#define EXAMPLE_COUNT (30)

VECTOR_TEMPLATE(Example)

int main(char**argv, int argc) {
	Example example;
	uint64_t length;
	uint64_t count;

	printf("\n");
	printf("Activity: Test the example string class\n");

	// Test we can create an object from our example class
	Example_construct_init(&example, "Hello World!");
	example_debug_print(&example);

	printf("\n");
	printf("Activity: Place an element in the vector\n");

	// Create a new vector
	Vector(Example) *vector = vector_new(Example)();
	
	vector_debug_print_space(Example)(vector);

	vector_push(Example)(vector, example);

	vector_debug_print_space(Example)(vector);

	example = vector_get(Example)(vector, 0);
	example_debug_print(&example);

	printf("\n");
	printf("Activity: Push examples to vector\n");

	// Create a bunch of examples, push them to the vector
	for (count = 0; count < EXAMPLE_COUNT; ++count) {
		Example_construct(&example);
		example_sprintf(&example, "Hello time %lu", count);
		vector_push(Example)(vector, example);
	}

	vector_debug_print_space(Example)(vector);

	printf("\n");
	printf("Activity: Output contents of vector\n");

	for (count = 0; count < EXAMPLE_COUNT; ++count) {
		Example example = vector_get(Example)(vector, count);
		example_debug_print(&example);
	}

	vector_debug_print_space(Example)(vector);

	printf("\n");
	printf("Activity: Pop contents of vector\n");

	for (count = 0; count < EXAMPLE_COUNT; ++count) {
		Example example = vector_pop(Example)(vector);
		example_debug_print(&example);
		Example_destruct(&example);
	}

	vector_debug_print_space(Example)(vector);

	printf("\n");
	printf("Activity: Remove last item from vector\n");

	example = vector_pop(Example)(vector);
	example_debug_print(&example);
	Example_destruct(&example);

	vector_debug_print_space(Example)(vector);

	printf("\n");
	printf("Activity: Push more examples to vector\n");

	// Create a bunch of examples, push them to the vector
	for (count = 0; count < EXAMPLE_COUNT; ++count) {
		Example_construct(&example);
		example_sprintf(&example, "Hello time %lu", count);
		vector_push(Example)(vector, example);
	}

	vector_debug_print_space(Example)(vector);

	printf("\n");
	printf("Activity: Delete the vector\n");
	vector_delete(Example)(vector);

	return 0;
}

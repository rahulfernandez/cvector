/* vim: set noet ts=2 sts=2 sw=2: */
/* SPDX-License-Identifier: BSD-2-Clause */
/* Copyright © 2024 David Llewellyn-Jones */

#include <stdio.h>

#include "cstring.h"
#include "cvector.h"

#define EXAMPLE_COUNT (30)

VECTOR_TEMPLATE(String)

int main(char**argv, int argc) {
	String string;
	uint64_t length;
	uint64_t count;

	printf("\n");
	printf("Activity: Test the example string class\n");

	// Test we can create an object from our string class
	String_construct_init(&string, "Hello World!");
	string_debug_print(&string);

	printf("\n");
	printf("Activity: Place an element in the vector\n");

	// Create a new vector
	Vector(String) *vector = vector_new(String)();
	
	vector_debug_print_space(String)(vector);

	vector_push(String)(vector, string);

	vector_debug_print_space(String)(vector);

	string = vector_get(String)(vector, 0);
	string_debug_print(&string);

	printf("\n");
	printf("Activity: Push strings to vector\n");

	// Create a bunch of strings, push them to the vector
	for (count = 0; count < EXAMPLE_COUNT; ++count) {
		String_construct(&string);
		string_sprintf(&string, "Hello time %lu", count);
		vector_push(String)(vector, string);
	}

	vector_debug_print_space(String)(vector);

	printf("\n");
	printf("Activity: Output contents of vector\n");

	for (count = 0; count < EXAMPLE_COUNT; ++count) {
		String string = vector_get(String)(vector, count);
		string_debug_print(&string);
	}

	vector_debug_print_space(String)(vector);

	printf("\n");
	printf("Activity: Pop contents of vector\n");

	for (count = 0; count < EXAMPLE_COUNT; ++count) {
		String string = vector_pop(String)(vector);
		string_debug_print(&string);
		String_destruct(&string);
	}

	vector_debug_print_space(String)(vector);

	printf("\n");
	printf("Activity: Remove last item from vector\n");

	string = vector_pop(String)(vector);
	string_debug_print(&string);
	String_destruct(&string);

	vector_debug_print_space(String)(vector);

	printf("\n");
	printf("Activity: Push more strings to vector\n");

	// Create a bunch of strings, push them to the vector
	for (count = 0; count < EXAMPLE_COUNT; ++count) {
		String_construct(&string);
		string_sprintf(&string, "Hello time %lu", count);
		vector_push(String)(vector, string);
	}

	vector_debug_print_space(String)(vector);

	printf("\n");
	printf("Activity: Delete the vector\n");
	vector_delete(String)(vector);

	return 0;
}

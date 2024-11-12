/* vim: set noet ts=2 sts=2 sw=2: */
/* SPDX-License-Identifier: BSD-2-Clause */
/* Copyright © 2024 David Llewellyn-Jones */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#include "example-class.h"

void Example_construct(Example *data) {
	Example_construct_init(data, "");
}

void Example_construct_init(Example *data, char const * const string) {
	if (data) {
		const uint64_t length = strlen(string);

		data->length = length;
		data->string = malloc(sizeof(char) * (length + 1));
		strncpy(data->string, string, length + 1);
	}
}

void Example_destruct(Example * data) {
	if (data->string) {
		printf("Destructing example class\n");
		free(data->string);
		data->string = NULL;
	}
	data->length = 0;
}

Example *example_new() {
	Example *data;
	
	data = malloc(sizeof(Example));
	Example_construct(data);

	return data;
}

Example *example_new_init(char const * const string) {
	Example *data;
	
	data = malloc(sizeof(Example));
	Example_construct_init(data, string);

	return data;
}

Example *example_delete(Example *data) {
	if (data) {
		Example_destruct(data);

		free(data);
	}
	return NULL;
}

void example_debug_print(Example *data) {
	printf("%lu: %s\n", data->length, data->string);
}

void example_sprintf(Example *data, char const * format, ...) {
	uint64_t length;
	va_list args;

	va_start (args, format);
	length = vsnprintf(NULL, 0, format, args);
	va_end (args);

	data->string = realloc(data->string, sizeof(char) * (length + 1));
	
	va_start (args, format);
	data->length = vsnprintf(data->string, (length + 1), format, args);
	va_end (args);
}



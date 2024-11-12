/* vim: set noet ts=2 sts=2 sw=2: */
/* SPDX-License-Identifier: BSD-2-Clause */
/* Copyright © 2024 David Llewellyn-Jones */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#include "cstring.h"

void String_construct(String *data) {
	String_construct_init(data, "");
}

void String_construct_init(String *data, char const * const string) {
	if (data) {
		const uint64_t length = strlen(string);

		data->length = length;
		data->string = malloc(sizeof(char) * (length + 1));
		strncpy(data->string, string, length + 1);
	}
}

void String_destruct(String * data) {
	if (data->string) {
		printf("Destructing string class\n");
		free(data->string);
		data->string = NULL;
	}
	data->length = 0;
}

String *string_new() {
	String *data;
	
	data = malloc(sizeof(String));
	String_construct(data);

	return data;
}

String *string_new_init(char const * const string) {
	String *data;
	
	data = malloc(sizeof(String));
	String_construct_init(data, string);

	return data;
}

String *string_delete(String *data) {
	if (data) {
		String_destruct(data);

		free(data);
	}
	return NULL;
}

void string_debug_print(String *data) {
	if (data)
		printf("%lu: %s\n", data->length, data->string);
	else 
		printf("No string available to print\n");
}

void string_sprintf(String *data, char const * format, ...) {
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



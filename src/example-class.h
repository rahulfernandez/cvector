/* vim: set noet ts=2 sts=2 sw=2: */
/* SPDX-License-Identifier: BSD-2-Clause */
/* Copyright © 2024 David Llewellyn-Jones */

#ifndef __EXAMPLE_CLASS_H__
#define __EXAMPLE_CLASS_H__

#include <stdint.h>

typedef struct _String String;

// We have to include the struct definition to use it in our vector
// The vector needs to know how large the struct is

struct _String {
	uint64_t length;
	char * string;
};

// Constructors and destructors use "String"

void String_construct(String *data);
void String_construct_init(String *data, char const * const string);
void String_destruct(String *data);

// Class methods use "string"

String *string_new();
String *string_new_init(char const * const string);
String *string_delete(String *data);

void string_sprintf(String *data, char const * format, ...);
void string_debug_print(String *data);

#endif // #ifdef __EXAMPLE_CLASS_H__


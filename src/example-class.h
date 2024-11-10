/* vim: set noet ts=2 sts=2 sw=2: */
/* SPDX-License-Identifier: BSD-2-Clause */
/* Copyright © 2024 David Llewellyn-Jones */

#ifndef __EXAMPLE_CLASS_H__
#define __EXAMPLE_CLASS_H__

#include <stdint.h>

typedef struct _Example Example;

// We have to include the struct definition to use it in our vector
// The vector needs to know how large the struct is

struct _Example {
	uint64_t length;
	char * string;
};

// Constructors and destructors use "Example"

void Example_construct(Example *data);
void Example_construct_init(Example *data, char const * const string);
void Example_destruct(Example * data);

// Class methods use "example"

Example *example_new();
Example *example_new_init(char const * const string);
Example *example_delete(Example *data);

void example_sprintf(Example *data, char const * format, ...);
void example_debug_print(Example *data);

#endif // #ifdef __EXAMPLE_CLASS_H__


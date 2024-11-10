/* vim: set noet ts=2 sts=2 sw=2: */
/* SPDX-License-Identifier: BSD-2-Clause */
/* Copyright © 2024 David Llewellyn-Jones */

#ifndef __VECTOR_H__
#define __VECTOR_H__

#include "example-class.h"

typedef struct _Vector Vector;

void vector_construct(Vector *data);
Vector *vector_new();
void vector_destruct(Vector * data);
Vector *vector_delete(Vector *data);

Example vector_get(Vector *data, uint64_t position);
void vector_push(Vector *data, Example example);
Example vector_pop(Vector *data);
uint64_t vector_length(Vector *data);

void vector_resize(Vector *data, uint64_t required);

void vector_debug_print_space(Vector *data);

#endif // #ifdef __VECTOR_H__


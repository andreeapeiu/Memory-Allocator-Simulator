//Peiu Andreea 314CA
#ifndef DUMP_H_
#define DUMP_H_
#include "nodes.h"
#include "lists.h"
#include "malloc.h"

void dump_memory(heap_info * heap, unsigned int num_malloc_calls,
				 unsigned int num_free_calls, unsigned int num_frag);

#endif

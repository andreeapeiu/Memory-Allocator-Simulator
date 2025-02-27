//Peiu Andreea 314CA
#ifndef malloc_h
#define malloc_h
#include "struct.h"
#include "nodes.h"
#include "lists.h"

void no_fragmentation(heap_info * *heap, dll_node_t *selected_node);

void fragmentation(heap_info **heap, dll_node_t *selected_node,
				   unsigned int nr);

void malloc_function(heap_info **heap, int num_bytes, int *num_frag,
					 int *malloc_calls);

#endif

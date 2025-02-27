// Peiu Andreea 314CA
#ifndef utils_h
#define utils_h
#include "malloc.h"
#include "nodes.h"
#include "struct.h"

void write(heap_info * heap, unsigned int adr, char *added_elem, int bytes,
		   unsigned int num_malloc_calls, unsigned int num_free_calls,
		   unsigned int num_frag, int length);

void read(heap_info *heap, unsigned int adr, int bytes,
		  unsigned int num_malloc_calls, unsigned int num_free_calls,
		  unsigned int num_frag);

#endif

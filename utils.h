//Peiu Andreea 314CA
#ifndef utils_h
#define utils_h
#include "struct.h"
#include "nodes.h"
#include "malloc.h"

heap_info * init_heap(unsigned int start_address, int nr, int bytes);

void free_function(heap_info *heap, unsigned long long adr, int *nr_frees);

void destroy_heap(heap_info *heap);

#endif

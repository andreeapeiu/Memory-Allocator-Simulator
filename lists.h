//Peiu Andreea 314CA
#ifndef lists_h
#define lists_h
#include "struct.h"
#include "nodes.h"

void dll_free(doubly_linked_list_t **pp_list);

doubly_linked_list_t *dll_create(unsigned int block_size, unsigned int *address,
								 int heap_size);

void insert_new_list(heap_info *heap, unsigned int adr, int block_size);

#endif

//Peiu Andreea 314CA
#ifndef nodes_h
#define nodes_h
#include "struct.h"

dll_node_t *dll_remove_nth_node(doubly_linked_list_t *list, unsigned int n);

void dll_free(doubly_linked_list_t **pp_list);

void dll_add_nth_node(doubly_linked_list_t *list, unsigned int n,
					  unsigned int adress, int block_size);

void add_adr(doubly_linked_list_t *list, unsigned int adress, int block_size);

#endif

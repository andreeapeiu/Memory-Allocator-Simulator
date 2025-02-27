//Peiu Andreea 314CA
#include "struct.h"
#include "utils.h"
#include "lists.h"

void dll_free(doubly_linked_list_t **pp_list)
{
	dll_node_t *nod = (*pp_list)->head;
	for (unsigned int i = 0; i < (*pp_list)->size; i++) {
		info_node *info = (info_node *)nod->data;
		dll_node_t *aux = nod->next;
		nod->next = NULL;
		nod->prev = NULL;

		if (info->text)
			free(info->text);
		free(nod->data);
		free(nod);
		nod = aux;
	}
	free(*pp_list);
	*pp_list = NULL;
}

doubly_linked_list_t *dll_create(unsigned int block_size, unsigned int *address,
								 int heap_size)
{
	doubly_linked_list_t *list = malloc(sizeof(doubly_linked_list_t));
	DIE(!list, "malloc failed");
	list->size = 0;
	list->head = NULL;
	unsigned int adr = *address;

	for (int i = 0; i < heap_size; i++) {
		dll_add_nth_node(list, i, adr, block_size);
		adr = adr + block_size;
	}
	*address = adr;
	return list;
}

void insert_new_list(heap_info *heap, unsigned int adr, int block_size)
{
	int index = heap->nr_lists - 1;
	doubly_linked_list_t *new_list = dll_create(block_size, &adr, 1);
	DIE(!new_list, "dll_create");

	for (unsigned int i = 0; i < heap->nr_lists; i++) {
		if (heap->lists[i]->size != 0) {
			info_node *head_info = (info_node *)heap->lists[i]->head->data;
			if (head_info->block_size > block_size) {
				index = i;
				break;
			}
		}
	}
	heap->lists = realloc(heap->lists, (heap->nr_lists + 1) *
										   sizeof(doubly_linked_list_t *));
	DIE(!heap->lists, "realloc");

	for (int i = heap->nr_lists; i > index; --i)
		heap->lists[i] = heap->lists[i - 1];

	heap->lists[index] = new_list;
	heap->nr_lists++;
	heap->total_nodes++;
}

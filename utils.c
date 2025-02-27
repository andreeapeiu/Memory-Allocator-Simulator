//Peiu Andreea 314CA
#include "struct.h"
#include "utils.h"

heap_info *init_heap(unsigned int start_address, int nr, int bytes)
{
	unsigned int block_size = 8;
	unsigned int adr = start_address;
	int heap_size = bytes / block_size; // Number of lists in the heap

	heap_info *heap = (heap_info *)malloc(sizeof(heap_info));
	DIE(!heap, "malloc failed");

	heap->nr_lists = nr;
	heap->total_nodes = 0;

	heap->occupied =
		(doubly_linked_list_t *)malloc(sizeof(doubly_linked_list_t));
	DIE(!heap->occupied, "malloc failed");
	heap->occupied->head = NULL;
	heap->occupied->size = 0;

	heap->lists = malloc(nr * sizeof(doubly_linked_list_t));
	DIE(!heap->lists, "malloc failed");
	heap->lists[0] = dll_create(block_size, &adr, heap_size);
	heap->total_nodes += heap_size;

	for (int i = 1; i < nr; i++) {
		block_size = block_size * 2;
		heap_size = heap_size / 2;
		heap->lists[i] =
			dll_create(block_size, &adr, heap_size);
		heap->total_nodes += heap_size;
	}
	return heap;
}

void free_function(heap_info *heap, unsigned long long adr, int *nr_frees)
{
	dll_node_t *current = heap->occupied->head;
	int ok = 0, poz = 0;
	while (current) {
		info_node *info = (info_node *)current->data;
		if (info->adr == adr) {
			ok = 1;
			break;
		}
		current = current->next;
	}

	if (ok == 0) {
		printf("Invalid free\n");
		return;
	}
	// means that ok=1
	(*nr_frees)++;
	current = heap->occupied->head;

	while (current) {
		info_node *info = (info_node *)current->data;
		if (info->adr == adr) {
			dll_node_t *nod = dll_remove_nth_node(heap->occupied, poz);
			info_node *info = (info_node *)nod->data;
			int nr = 0;
			for (unsigned int j = 0; j < heap->nr_lists; j++) {
				if (heap->lists[j]->size > 0) {
					info_node *head = (info_node *)heap->lists[j]->head->data;
					if (info->block_size == head->block_size) {
						add_adr(heap->lists[j], info->adr, info->block_size);
						nr = 1;
						heap->total_nodes++;
						break;
					}
				}
			}
			if (nr == 0)
				insert_new_list(heap, info->adr, info->block_size);
			if (info->text)
				free(info->text);
			free(nod->data);
			free(nod);
			return;
		}
		current = current->next;
		poz++;
	}
}

void destroy_heap(heap_info *heap)
{
	for (unsigned int i = 0; i < heap->nr_lists; i++)
		dll_free(&heap->lists[i]);
	free(heap->lists);
	dll_free(&heap->occupied);
	free(heap->occupied);
	free(heap);
}

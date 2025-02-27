//Peiu Andreea 314CA
#include "struct.h"
#include "malloc.h"

void no_fragmentation(heap_info **heap, dll_node_t *selected_node)
{
	info_node *selected_info = (info_node *)selected_node->data;
	add_adr((*heap)->occupied, selected_info->adr,
			selected_info->block_size);
}

void fragmentation(heap_info **heap, dll_node_t *selected_node,
				   unsigned int nr)
{
	int index = -1;
	dll_node_t *fragmented_block = (dll_node_t *)malloc(sizeof(dll_node_t));
	DIE(!fragmented_block, "malloc");

	info_node *fragmented_info = (info_node *)malloc(sizeof(info_node));
	DIE(!fragmented_info, "malloc");

	info_node *selected_info = (info_node *)selected_node->data;
	DIE(!selected_info, "malloc");

	fragmented_info->text = NULL;
	fragmented_info->adr = selected_info->adr + nr;
	fragmented_info->block_size = selected_info->block_size - nr;
	fragmented_block->prev = NULL;
	fragmented_block->next = selected_node->next;

	selected_info->block_size = nr;
	no_fragmentation(heap, selected_node);

	if (fragmented_block->next)
		fragmented_block->next->prev = fragmented_block;

	// Check if there is already a list in the heap with the remaining block
	// size
	for (unsigned int i = 0; i < (*heap)->nr_lists; ++i) {
		doubly_linked_list_t *current_list = (*heap)->lists[i];
		if (current_list->size > 0) {
			info_node *head_info = (info_node *)current_list->head->data;
			if (head_info->block_size == fragmented_info->block_size) {
				index = i;
				break;
			}
		}
	}

	if (index != -1) {
		add_adr((*heap)->lists[index], fragmented_info->adr,
				fragmented_info->block_size);

		if (fragmented_info->text)
			free(fragmented_info->text);
		free(fragmented_info);
		free(fragmented_block);
	} else {
		unsigned int index = 0;
		doubly_linked_list_t *new_list =
			dll_create(fragmented_info->block_size, &fragmented_info->adr, 1);
		DIE(!new_list, "dll_create");

		for (unsigned int i = 0; i < (*heap)->nr_lists; i++) {
			if ((*heap)->lists[i]->size != 0) {
				info_node *head = (info_node *)(*heap)->lists[i]->head->data;
				if (head->block_size > fragmented_info->block_size) {
					index = i;
					break;
				}
			}
		}
		(*heap)->lists =
			realloc((*heap)->lists,
					((*heap)->nr_lists + 1) * sizeof(doubly_linked_list_t *));
		DIE(!(*heap)->lists, "realloc");

		for (unsigned int i = (*heap)->nr_lists; i > index; --i)
			(*heap)->lists[i] = (*heap)->lists[i - 1];

		(*heap)->lists[index] = new_list;
		(*heap)->nr_lists++;
		(*heap)->total_nodes++;

		if (fragmented_info->text)
			free(fragmented_info->text);
		free(fragmented_info);
		free(fragmented_block);
	}
}

void malloc_function(heap_info **heap, int num_bytes, int *num_frag,
					 int *malloc_calls)
{
	dll_node_t *selected_node = NULL;
	doubly_linked_list_t *selected_list = NULL;
	unsigned int index;

	for (index = 0; index < (*heap)->nr_lists; ++index) {
		if ((*heap)->lists[index]->size == 0)
			continue;
		info_node *head_info = (info_node *)(*heap)->lists[index]->head->data;
		if (head_info->block_size >= num_bytes) {
			selected_list = (*heap)->lists[index];
			selected_node = dll_remove_nth_node(selected_list, 0);
			(*malloc_calls)++;
			break;
		}
	}

	if (!selected_list) {
		printf("Out of memory\n");
		return;
	}

	info_node *selected_info = (info_node *)selected_node->data;
	if (selected_info->block_size > num_bytes) {
		(*num_frag)++;
		fragmentation(heap, selected_node, num_bytes);
	} else {
		no_fragmentation(heap, selected_node);
	}

	if (selected_info->text)
		free(selected_info->text);
	free(selected_info);
	free(selected_node);
}

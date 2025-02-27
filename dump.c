//Peiu Andreea 314CA
#include "struct.h"
#include "malloc.h"
#include "nodes.h"

void dump_memory(heap_info *heap, unsigned int num_malloc_calls,
				 unsigned int num_free_calls, unsigned int num_frag)
{
	unsigned int total_bytes = 0, occupied_bytes = 0, total_freee_bytes = 0,
				 nr_free_blocks = 0, nr_occupied_blocks = 0;
	unsigned int *num_blocks_per_size =
		calloc(heap->nr_lists, sizeof(unsigned int));
	unsigned int *num_free_blocks =
		calloc(heap->nr_lists, sizeof(unsigned int));

	// Calculate memory allocation status
	for (unsigned int i = 0; i < heap->nr_lists; ++i) {
		doubly_linked_list_t *current_list = heap->lists[i];
		if (current_list->size != 0) {
			dll_node_t *curr_n = current_list->head;
			while (curr_n) {
				total_freee_bytes += ((info_node *)curr_n->data)->block_size;
				nr_free_blocks++;
				num_free_blocks[i]++;
				num_blocks_per_size[i]++;
				total_bytes += ((info_node *)curr_n->data)->block_size;
				curr_n = curr_n->next;
			}
		}
	}

	dll_node_t *current = heap->occupied->head;
	while (current) {
		info_node *occupied_info = (info_node *)current->data;
		occupied_bytes += occupied_info->block_size;
		total_bytes += occupied_info->block_size;
		nr_occupied_blocks++;
		current = current->next;
	}

	// Display memory allocation information
	printf("+++++DUMP+++++\n");
	printf("Total memory: %u bytes\n", total_bytes);
	printf("Total allocated memory: %u bytes\n", occupied_bytes);
	printf("Total free memory: %u bytes\n", total_freee_bytes);
	printf("Free blocks: %u\n", nr_free_blocks);
	printf("Number of allocated blocks: %u\n", nr_occupied_blocks);
	printf("Number of malloc calls: %u\n", num_malloc_calls);
	printf("Number of fragmentations: %u\n", num_frag);
	printf("Number of free calls: %u\n", num_free_calls);

	// Display block details
	for (unsigned int i = 0; i < heap->nr_lists; ++i) {
		if (heap->lists[i]->size != 0) {
			info_node *head_info = (info_node *)heap->lists[i]->head->data;
			unsigned int size = head_info->block_size;
			unsigned int num_blocks = num_blocks_per_size[i];
			if (num_blocks > 0) {
				printf("Blocks with %u bytes - %u free block(s) :", size,
					   num_free_blocks[i]);
				dll_node_t *curr_n = heap->lists[i]->head;
				while (curr_n) {
					info_node *block_info = (info_node *)curr_n->data;
					printf(" 0x%x", block_info->adr);
					curr_n = curr_n->next;
				}
				printf("\n");
			}
		}
	}

	printf("Allocated blocks :");

	dll_node_t *current_n = heap->occupied->head;
	while (current_n) {
		info_node *block_info = (info_node *)current_n->data;
		printf(" (0x%x - %u)", block_info->adr, block_info->block_size);
		current_n = current_n->next;
	}

	printf("\n-----DUMP-----\n");

	free(num_blocks_per_size);
	free(num_free_blocks);
}

//Peiu Andreea 314CA
#include "struct.h"
#include "nodes.h"

void write(heap_info *heap, unsigned int adr, char *added_elem, int bytes,
		   unsigned int num_malloc_calls, unsigned int num_free_calls,
		   unsigned int num_frag, int length)
{
	dll_node_t *current = heap->occupied->head;
	dll_node_t *selected_node = NULL;
	int ok = 0;
	unsigned int poz = 0;
	while (current) {
		if (((info_node *)current->data)->adr == adr) {
			ok = 1;
			selected_node = current;
			break;
		}
		current = current->next;
		poz++;
	}

	if (ok == 0) {
		printf("Segmentation fault (core dumped)\n");
		dump_memory(heap, num_malloc_calls, num_free_calls, num_frag);
		destroy_heap(heap);
		exit(0);
		return;
	}

	if (bytes > length)
		bytes = length;

	info_node *selected_info = (info_node *)selected_node->data;

	if (bytes > selected_info->block_size && !selected_node->next) {
		printf("Segmentation fault (core dumped)\n");
		dump_memory(heap, num_malloc_calls, num_free_calls, num_frag);
		destroy_heap(heap);
		exit(0);
		return;
	}

	int written_bytes = bytes;
	while (written_bytes > 0) {
		selected_info = (info_node *)selected_node->data;
		if (poz < heap->occupied->size && selected_node->next &&
			((info_node *)selected_node->next->data)->adr !=
				selected_info->adr + selected_info->block_size) {
			printf("Segmentation fault (core dumped)\n");
			dump_memory(heap, num_malloc_calls, num_free_calls, num_frag);
			destroy_heap(heap);
			exit(0);
			return;
		}

		if (!selected_info->text) {
			selected_info->text = malloc(selected_info->block_size + 1);
			DIE(!selected_info->text, "malloc");
		}
		if (written_bytes < selected_info->block_size)
			memcpy(selected_info->text, added_elem, written_bytes);
		else
			memcpy(selected_info->text, added_elem, selected_info->block_size);

		written_bytes -= selected_info->block_size;
		added_elem = added_elem + selected_info->block_size;
		selected_node = selected_node->next;
		poz++;
	}
}

void read(heap_info *heap, unsigned int adr, int bytes,
		  unsigned int num_malloc_calls, unsigned int num_free_calls,
		  unsigned int num_frag)
{
	dll_node_t *current = heap->occupied->head;
	dll_node_t *selected_node = NULL;
	int ok = 0, poz = 0;

	while (current) {
		info_node *info = (info_node *)current->data;
		if (adr - info->adr < (unsigned int)info->block_size) {
			ok = 1;
			selected_node = current;
			break;
		}
		current = current->next;
		poz++;
	}

	if (ok == 0) {
		printf("Segmentation fault (core dumped)\n");
		dump_memory(heap, num_malloc_calls, num_free_calls, num_frag);
		destroy_heap(heap);
		exit(0);
	}

	dll_node_t *start_node = selected_node;
	info_node *selected_info = (info_node *)selected_node->data;
	int offset = adr - selected_info->adr;
	int read_bytes =
		selected_info->block_size - offset; // how many bytes were read from
											// the first block

	while (read_bytes < bytes) {
		if (!selected_node->next ||
			((info_node *)selected_node->next->data)->adr !=
				selected_info->adr + selected_info->block_size) {
			printf("Segmentation fault (core dumped)\n");
			dump_memory(heap, num_malloc_calls, num_free_calls, num_frag);
			destroy_heap(heap);
			exit(0);
		}
		selected_node = selected_node->next;
		selected_info = (info_node *)selected_node->data;
		read_bytes += selected_info->block_size;
	}

	while (bytes > 0) {
		printf("%c", (((info_node *)start_node->data)->text)[offset]);
		bytes--;
		offset++;
		if (offset == ((info_node *)start_node->data)->block_size) {
			start_node = start_node->next;
			offset = 0;
		}
	}
	printf("\n");
}

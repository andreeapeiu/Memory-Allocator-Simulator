//Peiu Andreea 314CA
#include "utils.h"
#include "struct.h"
#include "malloc.h"
#include "nodes.h"
#include "lists.h"

int main(void)
{
	heap_info *heap;
	unsigned int start_adress = 0, adr = 0;
	int num_malloc_calls = 0, num_free_calls = 0, num_frag = 0;
	int bytes = 0, tip;
	char added_elem[MAX_STRING_SIZE];

	while (1) {
		char command[600];
		scanf("%s", command);
		if (strncmp(command, "INIT_HEAP", 9) == 0) {
			long nr;
			scanf("%x", &start_adress);
			scanf("%ld", &nr);
			scanf("%d", &bytes);
			scanf("%d", &tip);
			heap = init_heap(start_adress, nr, bytes);
		}
		if (strncmp(command, "MALLOC", 6) == 0) {
			int nr_bytes;
			scanf("%d", &nr_bytes);
			malloc_function(&heap, nr_bytes, &num_frag, &num_malloc_calls);
		}

		if (strncmp(command, "DUMP_MEMORY", 11) == 0)
			dump_memory(heap, num_malloc_calls, num_free_calls, num_frag);

		if (strncmp(command, "FREE", 4) == 0) {
			scanf("%x", &adr);
			free_function(heap, adr, &num_free_calls);
		}
		if (strncmp(command, "WRITE", 5) == 0) {
			scanf("%x", &adr);
			getc(stdin);
			getc(stdin);
			fgets(added_elem, MAX_STRING_SIZE, stdin);

			char *p = strrchr(added_elem, '"');
			*p = '\0'; // eliminate' "
			bytes = strtol(p + 2, NULL, 0);
			unsigned int length = strlen(added_elem);
			write(heap, adr, added_elem, bytes, num_malloc_calls,
				  num_free_calls, num_frag, length);
		}

		if (strncmp(command, "READ", 4) == 0) {
			scanf("%x", &adr);
			scanf("%d", &bytes);
			read(heap, adr, bytes, num_malloc_calls, num_free_calls, num_frag);
		}

		if (strncmp(command, "DESTROY_HEAP", 12) == 0) {
			destroy_heap(heap);
			exit(0);
			return 0;
		}
	}
	return 0;
}

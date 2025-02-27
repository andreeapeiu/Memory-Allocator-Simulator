//Peiu Andreea 314CA
#ifndef structures_h
#define structures_h
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIE(assertion, call_description)                                       \
	do {                                                                       \
		if (assertion) {                                                       \
			fprintf(stderr, "(%s, %d): ", __FILE__, __LINE__);                 \
			perror(call_description);                                          \
			exit(errno);                                                       \
		}                                                                      \
	} while (0)

#define MAX_STRING_SIZE 400

typedef struct info_node info_node;
struct info_node {
	unsigned int adr; // node address
	int block_size;	  // block dimmention
	char *text;		  // string to be stored
};

typedef struct dll_node_t dll_node_t;
struct dll_node_t {
	void *data;
	dll_node_t *prev, *next;
};

typedef struct doubly_linked_list_t doubly_linked_list_t;
struct doubly_linked_list_t {
	dll_node_t *head;
	unsigned int size;	   // how many nodes are in the list
};

typedef struct heap_info heap_info;
struct heap_info {
	unsigned int nr_lists;	// how many lists are in the heap
	int total_nodes;
	doubly_linked_list_t **lists;	// array with doubly linked lists
	doubly_linked_list_t *occupied; // a list with occupied nodes
};

#endif

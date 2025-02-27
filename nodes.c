//Peiu Andreea 314CA
#include "struct.h"
#include "nodes.h"

dll_node_t *dll_remove_nth_node(doubly_linked_list_t *list, unsigned int n)
{
	dll_node_t *removed_node = list->head;
	dll_node_t *current = list->head;
	if (n == 0) {
		list->head = current->next;
		if (list->head)
			list->head->prev = NULL;
		current->next = NULL;
		list->size--;
		return removed_node;
	}

	if (n >= list->size - 1)
		n = list->size - 1;

	if (n <= list->size - 1) {
		for (unsigned int i = 0; i < n - 1; i++)
			current = current->next;
		removed_node = current->next;
		current->next = removed_node->next;
		if (removed_node->next)
			removed_node->next->prev = current;
		removed_node->next = NULL;
		removed_node->prev = NULL;
		list->size--;
		return removed_node;
	}
	return NULL;
}

void dll_add_nth_node(doubly_linked_list_t *list, unsigned int n,
					  unsigned int adress, int block_size)
{
	dll_node_t *new_node = malloc(sizeof(dll_node_t));
	DIE(!new_node, "malloc failed");
	info_node *info = (info_node *)malloc(sizeof(info_node));
	DIE(!info, "malloc failed");
	info->adr = adress;
	info->block_size = block_size;
	info->text = NULL;
	new_node->data = info;

	if (list->size == 0) {
		new_node->next = NULL;
		new_node->prev = NULL;
		list->head = new_node;

	} else if (n == 0) {
		new_node->next = list->head;
		new_node->prev = NULL;
		list->head->prev = new_node;
		list->head = new_node;

	} else if (n >= list->size) {
		dll_node_t *current = list->head;
		for (unsigned int i = 0; i < list->size - 1; i++)
			current = current->next;
		new_node->next = NULL;
		new_node->prev = current;
		current->next = new_node;
	} else {
		dll_node_t *current = list->head;
		for (unsigned int i = 0; i < n; i++)
			current = current->next;
		new_node->next = current;
		new_node->prev = current->prev;
		current->prev->next = new_node;
		current->prev = new_node;
	}
	list->size++;
}

void add_adr(doubly_linked_list_t *list, unsigned int adress, int block_size)
{
	if (list->size == 0 || adress < ((info_node *)list->head->data)->adr) {
		dll_add_nth_node(list, 0, adress, block_size);
	} else {
		int poz = 0;
		dll_node_t *current = list->head;
		while (current) {
			if (((info_node *)current->data)->adr > adress)
				break;
			current = current->next;
			poz++;
		}

		dll_add_nth_node(list, poz, adress, block_size);
	}
}

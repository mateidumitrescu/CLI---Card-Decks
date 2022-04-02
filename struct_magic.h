#ifndef STRUCT_MAGIC_H
#define STRUCT_MAGIC_H

#define S_MAX 10

typedef struct card_t {
	int number;
	char symbol[S_MAX];
} card_t;

typedef struct dll_node_t {
	void *data;
	struct dll_node_t *next;
	struct dll_node_t *prev;
} dll_node_t;

typedef struct dll_list_t {
	dll_node_t *head;
	int data_size;
	int size;
} dll_list_t;

#endif
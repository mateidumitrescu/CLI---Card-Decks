// Copyright 2022 Dumitrescu Rares Matei mateidum828@gmail.com

#ifndef STRUCT_MAGIC_H_
#define STRUCT_MAGIC_H_

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

#endif  // STRUCT_MAGIC_H_

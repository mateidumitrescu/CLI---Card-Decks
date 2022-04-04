#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct_magic.h"

#define ARG 56


dll_list_t *create_deck_list(int data_size) {

	dll_list_t *deck_list = malloc(sizeof(*deck_list));
	deck_list->data_size = data_size;
	deck_list->size = 0;
	deck_list->head = NULL;

	return deck_list;
}

dll_list_t *create_card_list(int data_size) {

	dll_list_t *card_list = malloc(sizeof(*card_list));
	card_list->data_size = data_size;
	card_list->size = 0;
	card_list->head = NULL;

	return card_list;
}

int is_valid_card(int number, char symbol[S_MAX]) {
	if (number > 14 || number < 1) {
		printf("The provided card is not a valid one.\n");
		return 0;
	}

	if (strcmp(symbol, "HEART") == 0 ||
		strcmp(symbol, "SPADE") == 0 ||
		strcmp(symbol, "CLUB") == 0 ||
		strcmp(symbol, "DIAMOND") == 0) {
		return 1;
	}

	printf("The provided card is not a valid one.\n");
	return 0;
}

void free_card_list(dll_list_t **card_list) {
	dll_node_t *current_card = (*card_list)->head;
	while (current_card != NULL) {
		dll_node_t *aux = current_card->next;
		free(current_card->data);
		free(current_card);
		current_card = aux;
	}
	free(*card_list);
}

int count_arguments(char arguments[ARG]) {
	char *p = strtok(arguments, " ");
	int count = 0;
	while (p != NULL) {
		count++;
		p = strtok(NULL, " ");
	}
	return count;
}

void add_card_in_list(dll_list_t *card_list, void* data) {
	dll_node_t *card = malloc(sizeof(*card));
	card->data = malloc(card_list->data_size);
	memcpy(card->data, data, card_list->data_size);

	if (card_list->size == 0) {
		card_list->head = card;
		card_list->head->next = NULL;
		card_list->head->prev = NULL;
		card_list->size = 1;
		return;
	}

	dll_node_t *current = card_list->head;
	dll_node_t *prev = NULL;
	while(current != NULL) {
		prev = current;
		current = current->next;
	}

	prev->next = card;
	card->prev = prev;
	card->next = NULL;
	card_list->size++;
}

void add_deck_in_list(dll_list_t *deck_list, void *data) {
	dll_node_t *deck = malloc(sizeof(*deck));
	deck->data = malloc(deck_list->data_size);
	memcpy(deck->data, data, deck_list->data_size);

	if (deck_list->size == 0) {
		deck_list->head = deck;
		deck_list->head->next = NULL;
		deck_list->head->prev = NULL;
		deck_list->size = 1;
		return;
	}

	dll_node_t *prev = NULL;
	dll_node_t *current = deck_list->head;
	while (current != NULL) {
		prev = current;
		current = current->next;
	}

	prev->next = deck;
	deck->prev = prev;
	deck->next = NULL;
	deck_list->size++;
}

void start_add_deck(int data_size_card_list, dll_list_t *deck_list) {
	int number_of_cards;
	scanf("%d", &number_of_cards);
	char buffer[ARG];
	fgets(buffer, ARG, stdin);
	if (strlen(buffer) > 1) {
		printf("Invalid command. Please try again.\n");
		return;
	}
	card_t *card_info = malloc(sizeof(*card_info));
	int count = 0;
	dll_list_t *card_list = create_card_list(data_size_card_list);
	while (count < number_of_cards) {
		scanf("%d", &card_info->number);
		scanf("%s", card_info->symbol);
		fgets(buffer, ARG, stdin);
		if (strlen(buffer) > 1) {
			count--;
			printf("Invalid command. Please try again.\n");
			//no incrementation so we could add number_of_cards cards in list
		} else if (is_valid_card(card_info->number, card_info->symbol)) {
			add_card_in_list(card_list, card_info);
		} else {
			count--;
		}
		count++;
	}
	free(card_info);
	add_deck_in_list(deck_list, card_list);
	free(card_list);//auxiliar
	printf("The deck was successfully created with %d cards.\n", number_of_cards);
}

//CHECK FREES !!!!!!!!!!!!!!!!!!!!!!!!
void free_all(dll_list_t **deck_list) {

	if ((*deck_list)->size == 0) {
		free(*deck_list);
		return;
	}

	dll_node_t *current_deck = (*deck_list)->head;
	int count = 0;
	while (count < (*deck_list)->size) {
		dll_list_t *card_list = (dll_list_t *)(current_deck->data);
		dll_node_t *aux = current_deck->next;
		free_card_list(&card_list);

		free(current_deck);
		current_deck = aux;
		count++;
	}

	free((*deck_list));
}

void show_all(dll_list_t *deck_list) {
	if (deck_list->size == 0)
		return;

	dll_node_t *current_deck = deck_list->head;
	int index = 0;
	while (current_deck != NULL) {
		printf("Deck %d:\n", index);
		dll_list_t *card_list = (dll_list_t *)current_deck->data;
		dll_node_t *current_card = card_list->head;
		while (current_card != NULL) {
			card_t *info = (card_t *)current_card->data;
			printf("\t%d %s\n", info->number, info->symbol);
			current_card = current_card->next;
		}
		current_deck = current_deck->next;
		index++;
	}
}

void show_deck_by_index(dll_list_t *deck_list) {
	int index;
	char buffer[ARG];
	scanf("%d", &index);
	fgets(buffer, ARG, stdin);
	if (strlen(buffer) > 1) {
		printf("Invalid command. Please try again.\n");
		return;
	}
	if (index >= deck_list->size || index < 0) {
		printf("The provided index is out of bounds for the deck list.\n");
		return;
	}
	printf("Deck %d:\n", index);
	dll_node_t *current_deck = deck_list->head;
	while (index > 0) {
		current_deck = current_deck->next;
		index--;
	}
	dll_list_t *card_list = (dll_list_t *)current_deck->data;
	dll_node_t *current_card = card_list->head;
	while (current_card != NULL) {
		card_t *info = (card_t *)current_card->data;
		printf("\t%d %s\n", info->number, info->symbol);
		current_card = current_card->next;
	}
}

void reverse_deck(dll_list_t *deck_list) {
	int index;
	char buffer[ARG];
	scanf("%d", &index);
	fgets(buffer, ARG, stdin);//buffer used to check number of arguments
	if (strlen(buffer) > 1) {
		printf("Invalid command. Please try again.\n");
		return;
	}
	if (index >= deck_list->size || index < 0) {
		printf("The provided index is out of bounds for the deck list.\n");
		return;
	}
	int copy_index = index;
	dll_node_t *current_deck = deck_list->head;
	while (index > 0) {
		current_deck = current_deck->next;
		index--;
	}
	dll_list_t *card_list = (dll_list_t *)current_deck->data;
	dll_node_t *current_card = card_list->head;
	dll_node_t *prev_card = NULL;
	while (current_card != NULL) {
		prev_card = current_card;
		current_card = current_card->next;
	}
	current_card = prev_card;
	card_list->head = current_card;
	dll_node_t *aux_next, *aux_prev;
	while (current_card != NULL) {//reversing starts here
		aux_next = current_card->prev;
		aux_prev = current_card->next;
		current_card->prev = aux_prev;
		current_card->next = aux_next;
		current_card = aux_next;
	}
	printf("The deck %d was successfully reversed.\n", copy_index);
}

void delete_deck(dll_list_t *deck_list) {
	int index;
	char buffer[ARG];
	scanf("%d", &index);
	fgets(buffer, ARG, stdin);
	if (strlen(buffer) > 1) {
		printf("Invalid command. Please try again.\n");
		return;
	}
	if (index >= deck_list->size || index < 0) {
		printf("The provided index is out of bounds for the deck list.\n");
		return;
	}
	dll_node_t *current_deck = deck_list->head;
	int copy_index = index;
	while (index > 0) {
		current_deck = current_deck->next;
		index--;
	}
	dll_list_t *card_list = (dll_list_t *)current_deck->data;

	if (current_deck == deck_list->head && deck_list->size == 1) {//special case
		free_card_list(&card_list);
		deck_list->size--;
		
		free(current_deck);
		deck_list->head = NULL;
		printf("The deck %d was successfully deleted.\n", copy_index);
		return;
	} else if (current_deck == deck_list->head) {
		free_card_list(&card_list);
		deck_list->size--;
		deck_list->head = current_deck->next;
		deck_list->head->prev = NULL;
		
		free(current_deck);
		printf("The deck %d was successfully deleted.\n", copy_index);
		return;
	}

	if (current_deck->next == NULL) {//reached end of list
		free_card_list(&card_list);//free card list first
		deck_list->size--;
		current_deck->prev->next = NULL;
		
		free(current_deck);
		printf("The deck %d was successfully deleted.\n", copy_index);
		return;
	}

	//general case for deleting a deck inside the deck list
	current_deck->prev->next = current_deck->next;
	current_deck->next->prev = current_deck->prev;//deck is now out of list
	free_card_list(&card_list);
	
	free(current_deck);
	deck_list->size--;
	printf("The deck %d was successfully deleted.\n", copy_index);
}



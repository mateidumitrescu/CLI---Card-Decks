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

void delete_card(dll_list_t *deck_list) {
	int index_deck, index_card;
	scanf("%d%d", &index_deck, &index_card);
	char buffer[ARG];
	fgets(buffer, ARG, stdin);
	if (strlen(buffer) > 1) {
		printf("Invalid command. Please try again.\n");
		return;
	}

	if (index_deck >= deck_list->size || index_deck < 0) {
		printf("The provided index is out of bounds for the deck list.\n");
		return;
	}
	int copy_index_deck;
	copy_index_deck = index_deck;

	dll_node_t *current_deck = deck_list->head;
	while (index_deck > 0) {
		current_deck = current_deck->next;
		index_deck--;
	}
	dll_list_t *card_list = (dll_list_t *)current_deck->data;
	if (index_card >= card_list->size || index_card < 0) {
		printf("The provided index is out of bounds for deck %d.\n", copy_index_deck);
		return;
	}
	dll_node_t *current_card = card_list->head;
	while (index_card > 0) {
		current_card = current_card->next;
		index_card--;
	}

	if (current_card == card_list->head && card_list->size == 1) {
		// special case for only one card in list
		// deck must be deleted
		free_card_list(&card_list);
		deck_list->size--;
		if (deck_list->size == 0) {
			deck_list->head = NULL;
		} else if (current_deck->next == NULL) {
			current_deck->prev->next = NULL;
		} else {
			current_deck->prev->next = current_deck->next;
			current_deck->next->prev = current_deck->prev;
		}
		free(current_deck);
		printf("The card was successfully deleted from deck %d.\n", copy_index_deck);
		return;
	}

	if (current_card == card_list->head) {// special case for index 0
		card_list->size--;
		card_list->head = current_card->next;
		card_list->head->prev = NULL;
		free(current_card->data);
		free(current_card);
		printf("The card was successfully deleted from deck %d.\n", copy_index_deck);
		return;
	}

	if (current_card->next == NULL) {
		//special case for last card in deck
		card_list->size--;
		current_card->prev->next = NULL;
		free(current_card->data);
		free(current_card);
		printf("The card was successfully deleted from deck %d.\n", copy_index_deck);
		return;
	}

	// general case for a card deleted inside the list
	card_list->size--;
	current_card->prev->next = current_card->next;
	current_card->next->prev = current_card->prev;
	free(current_card->data);
	free(current_card);
	printf("The card was successfully deleted from deck %d.\n", copy_index_deck);
}

void start_adding_cards(dll_list_t *card_list, int number_of_cards) {
	int index = 0;
	char buffer[ARG];
	card_t *info = malloc(sizeof(*info));
	while (index < number_of_cards) {
		scanf("%d%s", &info->number, info->symbol);
		fgets(buffer, ARG, stdin);
		if (strlen(buffer) > 1) {
			index--;
			printf("Invalid command. Please try again.\n");
			//no incrementation so we could add number_of_cards cards in list
		} else if (is_valid_card(info->number, info->symbol)) {
			add_card_in_list(card_list, info);
		} else {
			index--;
		}
		index++;
	}
	free(info);
}

void add_cards(dll_list_t *deck_list) {
	int index_deck, number_of_cards;
	scanf("%d%d", &index_deck, &number_of_cards);
	char buffer[ARG];
	fgets(buffer, ARG, stdin);
	if (strlen(buffer) > 1) {
		printf("Invalid command. Please try again.\n");
		return;
	}
	if (index_deck < 0 || index_deck >= deck_list->size) {
		printf("The provided index is out of bounds for the deck list.\n");
		return;
	}
	int copy_index = index_deck;
	dll_node_t *current_deck = deck_list->head;
	while (index_deck > 0) {
		current_deck = current_deck->next;
		index_deck--;
	}
	dll_list_t *card_list = (dll_list_t *)current_deck->data;
	// adding cards in deck starts here
	start_adding_cards(card_list, number_of_cards);
	
	printf("The cards were successfully added to deck %d.\n", copy_index);
}

void print_deck_number(dll_list_t *deck_list) {
	char buffer[ARG];
	fgets(buffer, ARG, stdin);
	if (strlen(buffer) > 1) {
		printf("Invalid command. Please try again.\n");
		return;
	}
	printf("The number of decks is %d.\n", deck_list->size);
}

void print_len_deck(dll_list_t *deck_list) {
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
	int copy_index = index;
	dll_node_t *current_deck = deck_list->head;
	while (index > 0) {
		current_deck = current_deck->next;
		index--;
	}
	// we reached the deck we want to get the length of
	dll_list_t *card_list = (dll_list_t *)current_deck->data;
	printf("The length of deck %d is %d.\n", copy_index, card_list->size);
}

void end_point_first(dll_list_t *card_list) {
	dll_node_t *prev = NULL;
	dll_node_t *current_card = card_list->head;
	while (current_card != NULL) {
		prev = current_card;
		current_card = current_card->next;
	}
	prev->next = card_list->head;
	card_list->head->prev = prev;
}

void start_shuffle(dll_list_t *card_list) {
	if (card_list->size == 1)
		return;
	int middle = card_list->size / 2;
	end_point_first(card_list);
	int index = 0;
	dll_node_t *current_card = card_list->head;
	while (index < middle) {
		current_card = current_card->next;
		index++;
	}
	dll_node_t *prev = current_card->prev;
	current_card->prev = NULL;
	card_list->head = current_card;
	prev->next = NULL;
}

void shuffle_deck(dll_list_t *deck_list) {
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
	int copy_index = index;
	dll_node_t *current_deck = deck_list->head;
	while (index > 0) {
		current_deck = current_deck->next;
		index--;
	}
	//reached deck that we want to shuffle
	dll_list_t *card_list = (dll_list_t *)current_deck->data;
	start_shuffle(card_list);
	printf("The deck %d was successfully shuffled.\n", copy_index);
}

dll_list_t *reach_deck(dll_list_t *deck_list, int index) {
	dll_node_t *current_deck = deck_list->head;
	while (index > 0) {
		current_deck = current_deck->next;
		index--;
	}
	dll_list_t *card_list = (dll_list_t *)current_deck->data;
	return card_list;
}

void del_index_deck(dll_list_t *deck_list, int index) {
	dll_node_t *current_deck = deck_list->head;
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
		return;
	} else if (current_deck == deck_list->head) {
		free_card_list(&card_list);
		deck_list->size--;
		deck_list->head = current_deck->next;
		deck_list->head->prev = NULL;
		
		free(current_deck);
		return;
	}

	if (current_deck->next == NULL) {//reached end of list
		free_card_list(&card_list);//free card list first
		deck_list->size--;
		current_deck->prev->next = NULL;
		
		free(current_deck);
		return;
	}

	//general case for deleting a deck inside the deck list
	current_deck->prev->next = current_deck->next;
	current_deck->next->prev = current_deck->prev;//deck is now out of list
	free_card_list(&card_list);
	
	free(current_deck);
	deck_list->size--;
}

void merge_decks(dll_list_t *deck_list) {
	int index1, index2;
	scanf("%d%d", &index1, &index2);
	char buffer[ARG];
	fgets(buffer, ARG, stdin);
	if (strlen(buffer) > 1) {
		printf("Invalid command. Please try again.\n");
		return;
	}
	if (index1 >= deck_list->size || index1 < 0 ||
		index2 >= deck_list->size || index2 < 0) {
		printf("The provided index is out of bounds for the deck list.\n");
		return;
	}
	// new list starts here
	dll_list_t *card_list_1 = reach_deck(deck_list, index1);
	dll_list_t *card_list_2 = reach_deck(deck_list, index2);
	// we have the 2 lists that we want to merge
	dll_list_t *new_list = create_card_list(card_list_2->data_size);
	dll_node_t *current_card_1 = card_list_1->head;
	dll_node_t *current_card_2 = card_list_2->head;

	while (current_card_1 != NULL && current_card_2 != NULL) {
		add_card_in_list(new_list, current_card_1->data);
		add_card_in_list(new_list, current_card_2->data);
		current_card_1 = current_card_1->next;
		current_card_2 = current_card_2->next;
	}
	

	while (current_card_2 != NULL) {
		add_card_in_list(new_list, current_card_2->data);
		current_card_2 = current_card_2->next;
	}
	while (current_card_1 != NULL) {
		add_card_in_list(new_list, current_card_1->data);
		current_card_1 = current_card_1->next;
	}

	add_deck_in_list(deck_list, new_list);// new list added
	free(new_list);// auxiliar
	if (index1 > index2) {
		del_index_deck(deck_list, index1);
		del_index_deck(deck_list, index2);
	} else {
		del_index_deck(deck_list, index2);
		del_index_deck(deck_list, index1);
	}
	
	printf("The deck %d and the deck %d were successfully merged.\n", index1, index2);
}

void insert_deck(dll_list_t *deck_list, dll_list_t *list, int index) {
	dll_node_t *new_deck = malloc(sizeof(*new_deck));
	new_deck->data = malloc(deck_list->data_size);
	memcpy(new_deck->data, list, deck_list->data_size);

	dll_node_t *current_deck = deck_list->head;
	while (index > 0) {
		current_deck = current_deck->next;
		index--;
	}
	if (current_deck->next == NULL) {// we reached end of deck list
		current_deck->next = new_deck;
		new_deck->prev = current_deck;
		new_deck->next = NULL;
		deck_list->size++;
		return;
	}
	// general case for inserting a deck
	new_deck->next = current_deck->next;
	current_deck->next = new_deck;
	new_deck->prev = current_deck;
	new_deck->next->prev = new_deck;
	deck_list->size++;
}

void split_deck(dll_list_t *deck_list) {
	int index_deck;
	int index_split;
	scanf("%d%d", &index_deck, &index_split);
	char buffer[ARG];
	fgets(buffer, ARG, stdin);
	if (strlen(buffer) > 1) {
		printf("Invalid command. Please try again.\n");
		return;
	}
	if (index_deck < 0 || index_deck >= deck_list->size) {
		printf("The provided index is out of bounds for the deck list.\n");
		return;
	}
	dll_list_t *card_list = reach_deck(deck_list, index_deck);
	if (index_split >= card_list->size || index_split < 0) {
		printf("The provided index is out of bounds for deck %d.\n", index_deck);
		return;
	}
	
	if (index_split == 0) {
		printf("The deck %d was successfully split by index %d.\n", index_deck, index_split);
		return;
	}
	int copy_index = index_split;
	dll_list_t *second_list = create_card_list(card_list->data_size);
	dll_node_t *prev = NULL;
	dll_node_t *current_card = card_list->head;
	while (copy_index > 0) {
		prev = current_card;
		current_card = current_card->next;
		copy_index--;
	}
	int count = 0;
	
	while (current_card != NULL) {
		dll_node_t *aux = current_card->next;
		add_card_in_list(second_list, current_card->data);
		free(current_card->data);
		free(current_card);//we have to free old data
		count++;
		current_card = aux;
	}// we have the second list created, we have to insert it in deck list
	prev->next = NULL;
	card_list->size -= count;// new size for initial card list
	insert_deck(deck_list, second_list, index_deck);
	free(second_list);// auxiliar
	printf("The deck %d was successfully split by index %d.\n", index_deck, index_split);
}

void compare_cards(dll_node_t *current_card, dll_node_t *compare_card) {
	card_t *info_1 = (card_t *)current_card->data;
	card_t *info_2 = (card_t *)compare_card->data;
	if (info_1->number == info_2->number && strcmp(info_1->symbol, info_2->symbol) == 0) {
		return;
	}
	if (info_1->number > info_2->number) {
		card_t *aux = current_card->data;
		current_card->data = compare_card->data;
		compare_card->data = aux;
	} else if (info_1->number == info_2->number) {
		if (strcmp(info_2->symbol, "HEART") == 0 && strcmp(info_1->symbol, "CLUB") == 0) {
			card_t *aux = current_card->data;
			current_card->data = compare_card->data;
			compare_card->data = aux;
		} else if (strcmp(info_2->symbol, "SPADE") == 0 && strcmp(info_1->symbol, "CLUB") == 0) {
			card_t *aux = current_card->data;
			current_card->data = compare_card->data;
			compare_card->data = aux;
		} else if (strcmp(info_2->symbol, "DIAMOND") == 0 && strcmp(info_1->symbol, "CLUB") == 0) {
			card_t *aux = current_card->data;
			current_card->data = compare_card->data;
			compare_card->data = aux;
		} else if (strcmp(info_2->symbol, "HEART") == 0 && strcmp(info_1->symbol, "DIAMOND") == 0) {
			card_t *aux = current_card->data;
			current_card->data = compare_card->data;
			compare_card->data = aux;
		} else if (strcmp(info_2->symbol, "SPADE") == 0 && strcmp(info_1->symbol, "DIAMOND") == 0) {
			card_t *aux = current_card->data;
			current_card->data = compare_card->data;
			compare_card->data = aux;
		} else if (strcmp(info_2->symbol, "HEART") == 0 && strcmp(info_1->symbol, "SPADE") == 0) {
			card_t *aux = current_card->data;
			current_card->data = compare_card->data;
			compare_card->data = aux;
		}
	}
}

void sort_deck(dll_list_t *deck_list) {
	int index;
	scanf("%d", &index);
	char buffer[ARG];
	fgets(buffer, ARG, stdin);
	if (strlen(buffer) > 1) {
		printf("Invalid command. Please try again.\n");
		return;
	}
	if (index >= deck_list->size || index < 0) {
		printf("The provided index is out of bounds for the deck list.\n");
		return;
	}
	dll_list_t *card_list = reach_deck(deck_list, index);
	dll_node_t *current_card = card_list->head;
	dll_node_t *compare_card;
	for (int i = 0; i < card_list->size; i++) {
		compare_card = current_card;
		for (int j = i + 1; j < card_list->size; j++) {
			compare_card = compare_card->next;
			compare_cards(current_card, compare_card);
		}
		current_card = current_card->next;
	}
	printf("The deck %d was successfully sorted.\n", index);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct_magic.h"
#include "utils.h"

#define C_MAX 128
#define ARG 56
#define S 256

int main(void) {

	char command[C_MAX];
	int magic = 1;
	int data_size_deck_list = sizeof(dll_list_t);
	int data_size_card_list = sizeof(card_t);
	
	dll_list_t *deck_list = create_deck_list(data_size_deck_list);

	while (magic) {
		scanf("%s", command);
		if (strcmp(command, "EXIT") == 0) {
			free_all(&deck_list);
			magic = 0;
		} else if (strcmp(command, "ADD_DECK") == 0) {
			start_add_deck(data_size_card_list, deck_list);
		} else if (strcmp(command, "SHOW_ALL") == 0) {
			show_all(deck_list);
		} else if (strcmp(command, "SHOW_DECK") == 0) {
			show_deck_by_index(deck_list);
		} else if (strcmp(command, "REVERSE_DECK") == 0) {
			reverse_deck(deck_list);
		} else if (strcmp(command, "DEL_DECK") == 0) {
			delete_deck(deck_list);
		} else if (strcmp(command, "DEL_CARD") == 0) {
			delete_card(deck_list);
		} else if (strcmp(command, "ADD_CARDS") == 0) {
			add_cards(deck_list);
		} else if (strcmp(command, "DECK_NUMBER") == 0) {
			print_deck_number(deck_list);
		} else if (strcmp(command, "DECK_LEN") == 0) {
			print_len_deck(deck_list);
		} else if (strcmp(command, "SHUFFLE_DECK") == 0) {
			shuffle_deck(deck_list);
		} else if (strcmp(command, "MERGE_DECKS") == 0) {
			merge_decks(deck_list);
		} else if (strcmp(command, "SPLIT_DECK") == 0) {
			split_deck(deck_list);
		} else if (strcmp(command, "SORT_DECK") == 0) {
			sort_deck(deck_list);	
		} else {
			char buffer[S];
			fgets(buffer, S, stdin);
			printf("Invalid command. Please try again.\n");
		}
	}

	return 0;
}
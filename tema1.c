#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct_magic.h"
#include "utils.h"

#define C_MAX 128
#define ARG 56

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
		}
	}

	return 0;
}
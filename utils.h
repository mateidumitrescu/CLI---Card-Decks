#ifndef UTILS_H
#define UTILS_H

#include "struct_magic.h"
#define ARG 56

//function to create a doubly linked list for decks
dll_list_t *create_deck_list(int data_size);

//function to create a doubly linked list for cards
dll_list_t *create_card_list(int data_size);

//function to check if a card is valid or not
int is_valid_card(int number, char symbol[S_MAX]);

//function to free a list of cards data
void free_card_list(dll_list_t **card_list);

//function to count the number of arguments
int count_arguments(char arguments[ARG]);

//function to add a card in a list of cards
void add_card_in_list(dll_list_t *card_list, void* data);

//function to add a deck in the list of decks
void add_deck_in_list(dll_list_t *deck_list, void *data);

//function to start ADD_DECK command
void start_add_deck(int data_size_card_list, dll_list_t *deck_list);

//function to free all malloc'd data
void free_all(dll_list_t **deck_list);

//function to show all decks
void show_all(dll_list_t *deck_list);

//function to show a deck by index
void show_deck_by_index(dll_list_t *deck_list);

//function to reverse cards in a deck
void reverse_deck(dll_list_t *deck_list);

//function to delete a deck in list
void delete_deck(dll_list_t *deck_list);

//function to delete <index_card> card from <index_deck> deck
void delete_card(dll_list_t *deck_list);

//function to add n cards in a deck
void start_adding_cards(dll_list_t *card_list, int number_of_cards);

//function to start adding cards in a deck
void add_cards(dll_list_t *deck_list);

//function to print the number of decks in the list of decks
void print_deck_number(dll_list_t *deck_list);

//function to get the length of a deck
void print_len_deck(dll_list_t *deck_list);

//function to make last card point to head and head to last
void end_point_first(dll_list_t *card_list);

//function to change pointers to shuffle deck
void start_shuffle(dll_list_t *card_list);

//function to start shuffle deck
void shuffle_deck(dll_list_t *deck_list);

//function to return the deck that we want to work with
dll_list_t *reach_deck(dll_list_t *deck_list, int index);

//function to delete a deck from an index given
void del_index_deck(dll_list_t *deck_list, int index);

//function to merge 2 decks
void merge_decks(dll_list_t *deck_list);

#endif
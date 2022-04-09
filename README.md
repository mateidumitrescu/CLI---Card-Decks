**Name: Dumitrescu Rares Matei**
**Group: 311CA**

## Tema 1 - Now You See Me

### Description:

This project uses double linked lists to store 2 types of lists:
- a list of decks which store lists of cards
- lists of cards stored in decks which store the data of cards
Example: list nodes Deck 0 Deck 1 store each of them 2 card lists:
3 SPADE  3 DIAMOND; 2 CLUB 10 HEART 5 CLUB. 
To do this, the project contains 3 data structures: one for
a list, one for a node, and one for card info. To be efficient,
the data structure for node contains one void* data so the program
can creatie a list in which each node contains a list in *data
and each node in this list contains a card info *data.
Commands used for running the program can be easily checked in main.c file
followed by arguments.

### Comments on project:

I think that this program could use less functions to run, so I think
that it can use same several functions to do the same thing. For example,
the 2 functions add_deck_in_list and add_card_in_list and the 2 functions
create_card_list and create_deck_list are basically the same thing, because
they just get different arguments.

The main thing that I learned doing this project is to be careful on
mallocs and frees and also on taking care of special cases when working
with lists.
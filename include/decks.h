#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Deck {
    char* label;
    Flashcard* first;
    Flashcard* last;
    struct Deck* next;
} Deck;

typedef struct Decks {
    Deck* first;
    Deck* last;
} Decks;
Decks* startDecks();
void viewDecks(Decks* decks);
Deck* createDeck(char* dakeName);

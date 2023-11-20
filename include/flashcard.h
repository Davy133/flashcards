#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Flashcard {
    char* question;
    char* answer;
    struct Flashcard* next;
} Flashcard;

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

Flashcard* createFlashcard(const char* front, const char* back);
void deleteFlashcard(Flashcard* card);
void updateFlashcard(Flashcard* card, const char* front, const char* back);
const char* getFlashcardFront(const Flashcard* card);

Decks* startDecks();
void viewDecks(Decks* decks);
Deck* createDeck(char* dakeName);
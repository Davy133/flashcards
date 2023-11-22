#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cards.h>


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
Deck* createDeck(char* deckName);
void deleteDeck(Deck* deck);
void viewDecks(Decks* decks);

void addFlashcardToDeck(Deck* deck, Flashcard* card);
void removeFlashcardFromDeck(Deck* deck, Flashcard* card);
void updateFlashcardFromDeck(Deck* deck, Flashcard* card, const char* front, const char* back);
void viewFlashcardsFromDeck(Deck* deck);
void studyDeck(Deck* deck);

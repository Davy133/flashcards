#pragma once
#include "cJSON.h"
#include "deck_serializer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cards.h"

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
Deck* createDeck(char* deckName, cJSON* user_context);
void deleteDeck(Deck* deck, cJSON* user_context);
void viewDecks(Decks* decks, cJSON* user_context);

void addFlashcardToDeck(Deck* deck, Flashcard* card);
void removeFlashcardFromDeck(Deck* deck, Flashcard* card);
void updateFlashcardFromDeck(Deck* deck, Flashcard* card, const char* front, const char* back);
void viewFlashcardsFromDeck(Deck* deck);
void studyDeck(Deck* deck);

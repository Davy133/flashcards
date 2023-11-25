#pragma once
#include "common.h"
#include "deck_serializer.h"
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

void createDeck(char* deckName, cJSON* user_context);
void deleteDeck(int position, cJSON* user_context);
void viewDecks(cJSON* user_context);
void viewDeck(cJSON* user_context, int position);
void updateDeck(cJSON* user_context, int position, const char* newLabel);

void addFlashcardToDeck(cJSON* user_context, int deck_position, Flashcard* card);
void removeFlashcardFromDeck(cJSON* user_context, int deck_position, int flashcard_position);
void updateFlashcardFromDeck(cJSON* user_context, int deck_position, int flashcard_position, const char* newFront, const char* newBack);
void viewFlashcardsFromDeck(cJSON* user_context, int deck_position);

void enqueueCard(Deck* deck, Flashcard* card);
Flashcard* dequeueCard(Deck* deck); 

void sortDeck(Deck* deck);
void studyDeck(Deck* deck);

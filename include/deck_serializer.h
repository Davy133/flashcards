#pragma once
#include "cards.h"
#include "decks.h"
#include "cJSON.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Deck Deck;
typedef struct Decks Decks;

// Function declarations
Deck* deckFromJson(cJSON* json, cJSON* user_context);
void saveDeckToFile(Decks* deck, const char* filename);
Deck* loadDeckFromFile(const char* filename, cJSON* user_context);
cJSON* deckToJson(Deck* deck);

// cJSON* deckToJson(Deck* deck);
// Deck* deckFromJson(cJSON* json, cJSON* user_context);
// void saveDeckToFile(Decks* deck, const char* filename);
// Deck* loadDeckFromFile(const char* filename, cJSON* user_context);

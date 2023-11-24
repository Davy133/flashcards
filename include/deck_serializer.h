#pragma once
#include "cards.h"
#include "decks.h"
#include "cJSON.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Deck Deck;
typedef struct Decks Decks;

Deck* deckFromJson(cJSON* json, cJSON* user_context);
void saveDeckToFile(cJSON* user_context, const char* filename, int deck_position);
Deck* loadDeckFromFile(const char* filename, cJSON* user_context);
cJSON* deckToJson(Deck* deck);

// cJSON* deckToJson(Deck* deck);
// Deck* deckFromJson(cJSON* json, cJSON* user_context);
// void saveDeckToFile(Decks* deck, const char* filename);
// Deck* loadDeckFromFile(const char* filename, cJSON* user_context);

#pragma once
#include "common.h"
#include "cards.h"
#include "decks.h"

typedef struct Deck Deck;
typedef struct Decks Decks;

Deck* deckFromJson(cJSON* json, cJSON* user_context);
cJSON* deckToJson(Deck* deck);
void saveDeckToFile(cJSON* user_context, const char* filename, int deck_position);
void loadDeckFromFile(const char* filename, cJSON* user_context);

#pragma once
#include <cards.h> 
#include <decks.h>  
#include <cJSON.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

cJSON* deckToJson(Deck* deck);
Deck* deckFromJson(cJSON* json);
void saveDeckToFile(Decks* deck, const char* filename);
Deck* loadDeckFromFile(const char* filename);

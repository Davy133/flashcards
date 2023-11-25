/*
Copyright (c) 2023 Davy Coelho and Contributors

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "deck_serializer.h"

cJSON* deckToJson(Deck* deck){
    cJSON* json = cJSON_CreateObject();
    cJSON* cards = cJSON_CreateArray();
    cJSON_AddItemToObject(json, "label", cJSON_CreateString(deck -> label));
    cJSON_AddItemToObject(json, "cards", cards);
    Flashcard* auxCard = deck -> first;
    while (auxCard != NULL){
        cJSON* card = cJSON_CreateObject();
        cJSON_AddItemToObject(card, "front", cJSON_CreateString(auxCard -> front));
        cJSON_AddItemToObject(card, "back", cJSON_CreateString(auxCard -> back));
        cJSON_AddItemToArray(cards, card);
        auxCard = auxCard -> next;
    }
    return json;
}

void saveDeckToFile(cJSON* user_context, const char* filename, int deck_position){
    cJSON* decks = cJSON_GetObjectItemCaseSensitive(user_context, "decks");
    cJSON* deck = cJSON_GetArrayItem(decks, deck_position);
    cJSON* jsonDeck = cJSON_GetObjectItemCaseSensitive(deck, "deck");
    cJSON* label = cJSON_GetObjectItemCaseSensitive(jsonDeck, "label");
    cJSON* cards = cJSON_GetObjectItemCaseSensitive(jsonDeck, "cards");
    cJSON* card = cards -> child;
    char jsonFilename[strlen(filename) + 5];
    strcpy(jsonFilename, filename);
    strcat(jsonFilename, ".json");
    FILE* file = fopen(jsonFilename, "w");
    fprintf(file, "{\n");
    fprintf(file, "\t\"label\": \"%s\",\n", label -> valuestring);
    fprintf(file, "\t\"cards\": [\n");
    while (card != NULL){
        fprintf(file, "\t\t{\n");
        fprintf(file, "\t\t\t\"front\": \"%s\",\n", card -> valuestring);
        fprintf(file, "\t\t\t\"back\": \"%s\"\n", card -> valuestring);
        fprintf(file, "\t\t},\n");
        card = card -> next;
    }
    fprintf(file, "\t]\n");
    fprintf(file, "}\n");
    fclose(file);
}

void loadDeckFromFile(const char* filename, cJSON* user_context){
    if (access(filename, F_OK) != -1){
        FILE* file = fopen(filename, "r");
        fseek(file, 0, SEEK_END);
        long fileSize = ftell(file);
        fseek(file, 0, SEEK_SET);
        char* jsonStr = malloc(fileSize + 1);
        fread(jsonStr, 1, fileSize, file);
        fclose(file);
        cJSON* json = cJSON_Parse(jsonStr);
        cJSON* cards = cJSON_GetObjectItem(json, "cards");
        cJSON* deckName = cJSON_GetObjectItem(json, "label");
        cJSON* card = cards -> child;
        createDeck(deckName -> valuestring, user_context);
        
    } else {
        printf("Deck não encontrado...\n");
    }
}

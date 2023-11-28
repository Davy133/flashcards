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

// cJSON* deckToJson(Deck* deck){
//     cJSON* json = cJSON_CreateObject();
//     cJSON* cards = cJSON_CreateArray();
//     cJSON_AddItemToObject(json, "label", cJSON_CreateString(deck -> label));
//     cJSON_AddItemToObject(json, "cards", cards);
//     Flashcard* auxCard = deck -> first;
//     while (auxCard != NULL){
//         cJSON* card = cJSON_CreateObject();
//         cJSON_AddItemToObject(card, "front", cJSON_CreateString(auxCard -> front));
//         cJSON_AddItemToObject(card, "back", cJSON_CreateString(auxCard -> back));
//         cJSON_AddItemToObject(card, "dueDate", cJSON_CreateNumber(auxCard -> dueDate));
//         cJSON_AddItemToObject(card, "sm2", cJSON_CreateObject());
//         cJSON* sm2 = cJSON_GetObjectItemCaseSensitive(card, "sm2");
//         cJSON_AddItemToObject(sm2, "interval", cJSON_CreateNumber(auxCard -> sm2 -> interval));
//         cJSON_AddItemToObject(sm2, "repetitions", cJSON_CreateNumber(auxCard -> sm2 -> repetitions));
//         cJSON_AddItemToObject(sm2, "easeFactor", cJSON_CreateNumber(auxCard -> sm2 -> easeFactor));
//         cJSON_AddItemToArray(cards, card);
//         auxCard = auxCard -> next;
//     }
//     return json;
// }

void saveDeckToFile(cJSON *user_context, const char *filename, int deck_position)
{
    cJSON *decks = cJSON_GetObjectItem(user_context, "decks");
    cJSON *deck = cJSON_GetArrayItem(decks, deck_position);
    char *jsonStr = cJSON_Print(deck);
    FILE *file = fopen(filename, "w");
    if (file != NULL)
    {
        fputs(jsonStr, file);
        fclose(file);
    }
    else
    {
        printf("Failed to save deck.\n");
    }
    free(jsonStr);
}

void loadDeckFromFile(const char *filename, cJSON *user_context)
{
    FILE *file = fopen(filename, "r");
    if (file != NULL)
    {
        fseek(file, 0, SEEK_END);
        long file_size = ftell(file);
        fseek(file, 0, SEEK_SET);
        char *json_data = malloc(file_size + 1);
        fread(json_data, 1, file_size, file);
        fclose(file);
        cJSON *deck = cJSON_Parse(json_data);
        free(json_data);
        cJSON *decks = cJSON_GetObjectItem(user_context, "decks");
        cJSON_AddItemToArray(decks, deck);
    }
    else
    {
        printf("Failed to load deck.\n");
    }
}

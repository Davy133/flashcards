#include "deck_serializer.h"
#include <stdio.h>
#include <unistd.h>

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

// Deck* deckFromJson(cJSON* json, cJSON* user_context){
//     cJSON* label = cJSON_GetObjectItem(json, "label");
//     Deck* deck = createDeck(label -> valuestring, user_context);
//     cJSON* cards = cJSON_GetObjectItem(json, "cards");
//     cJSON* card = cards -> child;
//     while (card != NULL){
//         addFlashcardToDeck(deck, createFlashcard(card -> valuestring, card -> valuestring));
//         card = card -> next;
//     }
//     return deck;
// }

void saveDeckToFile(cJSON* user_context, const char* filename, int deck_position){
    cJSON* decks = cJSON_GetObjectItemCaseSensitive(user_context, "decks");
    cJSON* deck = cJSON_GetArrayItem(decks, deck_position);
    cJSON* jsonDeck = cJSON_GetObjectItemCaseSensitive(deck, "deck");
    cJSON* label = cJSON_GetObjectItemCaseSensitive(jsonDeck, "label");
    cJSON* cards = cJSON_GetObjectItemCaseSensitive(jsonDeck, "cards");
    cJSON* card = cards -> child;
    char jsonFilename[strlen(filename) + 5]; // 5 is the length of ".json" plus null terminator
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

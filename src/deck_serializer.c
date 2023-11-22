#include <deck_serializer.h>

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

Deck* deckFromJson(cJSON* json, cJSON* user_context){
    cJSON* label = cJSON_GetObjectItem(json, "label");
    Deck* deck = createDeck(label -> valuestring, user_context);
    cJSON* cards = cJSON_GetObjectItem(json, "cards");
    cJSON* card = cards -> child;
    while (card != NULL){
        addFlashcardToDeck(deck, createFlashcard(card -> valuestring, card -> valuestring));
        card = card -> next;
    }
    return deck;
}

void saveDeckToFile(Decks* decks, const char* filename){
    cJSON* json = cJSON_CreateArray();
    cJSON* cards = cJSON_CreateObject();
    cJSON_AddItemToArray(json, cards);
    cJSON_AddItemToObject(cards, "cards", deckToJson(decks -> first));
    char* jsonStr = cJSON_Print(json);
    FILE* file = fopen(filename, "w");
    fwrite(jsonStr, 1, strlen(jsonStr), file);
    fclose(file);
    free(jsonStr);
    cJSON_Delete(json);

}

Deck* loadDeckFromFile(const char* filename, cJSON* user_context){
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
    Deck* auxDeck = createDeck(deckName -> valuestring, user_context);
}

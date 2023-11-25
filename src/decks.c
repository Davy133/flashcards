#include <decks.h>
#include <user_data_bus.h>

Decks* startDecks(){
    Decks* decks = (Decks*) malloc(sizeof(Decks));
    if (decks != NULL){
        decks -> first = NULL;
        decks -> last = NULL;
    } else {
        printf("Falha na inicialização...\n");
    }
    return decks;
}

void createDeck(char* deckName, cJSON* user_context){
    cJSON* decks = cJSON_GetObjectItemCaseSensitive(user_context, "decks");
    cJSON* deck = cJSON_CreateObject();
    cJSON_AddItemToArray(decks, deck);
    cJSON_AddItemToObject(deck, "deck", cJSON_CreateObject());
    cJSON* jsonDeck = cJSON_GetObjectItemCaseSensitive(deck, "deck");
    cJSON_AddItemToObject(jsonDeck, "label", cJSON_CreateString(deckName));
    cJSON_AddItemToObject(jsonDeck, "cards", cJSON_CreateArray());
    saveUserData(user_context);
    *user_context = *initializeUserDataBus();
}

void deleteDeck(int position, cJSON* user_context){
    cJSON* decks = cJSON_GetObjectItemCaseSensitive(user_context, "decks");
    cJSON* deck = cJSON_GetArrayItem(decks, position);
    int deckSize = cJSON_GetArraySize(decks);
    if (position >= 0 && position < deckSize) {
        cJSON_DeleteItemFromArray(decks, position);
        saveUserData(user_context);
        *user_context = *initializeUserDataBus();
    } else {
        printf("Posição inválida...\n");
    }
}

void viewDecks(cJSON* user_context){
    printf("Decks:\n");
    cJSON* decks = cJSON_GetObjectItemCaseSensitive(user_context, "decks");
    cJSON* deck = NULL;
    int index = 0;
    cJSON_ArrayForEach(deck, decks){
        cJSON* jsonDeck = cJSON_GetObjectItemCaseSensitive(deck, "deck");
        cJSON* label = cJSON_GetObjectItemCaseSensitive(jsonDeck, "label");
        printf("Deck %d: %s\n", index, label->valuestring);
        index++;
        }
}

void viewDeck(cJSON* user_context, int position){
    cJSON* decks = cJSON_GetObjectItemCaseSensitive(user_context, "decks");
    cJSON* deck = cJSON_GetArrayItem(decks, position);
    cJSON* jsonDeck = cJSON_GetObjectItemCaseSensitive(deck, "deck");
    cJSON* label = cJSON_GetObjectItemCaseSensitive(jsonDeck, "label");
    printf("Deck %d: %s\n", position, label->valuestring);
}

void updateDeck(cJSON* user_context, int position, const char* newLabel){
    cJSON* decks = cJSON_GetObjectItemCaseSensitive(user_context, "decks");
    cJSON* deck = cJSON_GetArrayItem(decks, position);
    int deckSize = cJSON_GetArraySize(decks);

    if (position >= 0 && position < deckSize) {
        cJSON* deck = cJSON_GetArrayItem(decks, position);
        cJSON* jsonDeck = cJSON_GetObjectItemCaseSensitive(deck, "deck");
        cJSON* label = cJSON_GetObjectItemCaseSensitive(jsonDeck, "label");
        label -> valuestring = strdup(newLabel);
        saveUserData(user_context);
        *user_context = *initializeUserDataBus();
    } else {
        printf("Posição inválida...\n");
    }
}

void addFlashcardToDeck(cJSON* user_context, int deck_position, Flashcard* card){
    cJSON* decks = cJSON_GetObjectItemCaseSensitive(user_context, "decks");
    cJSON* deck = cJSON_GetArrayItem(decks, deck_position);
    cJSON* jsonDeck = cJSON_GetObjectItemCaseSensitive(deck, "deck");
    cJSON* cards = cJSON_GetObjectItemCaseSensitive(jsonDeck, "cards");
    cJSON* cardJson = cJSON_CreateObject();
    cJSON_AddItemToArray(cards, cardJson);
    cJSON_AddItemToObject(cardJson, "front", cJSON_CreateString(card -> front));
    cJSON_AddItemToObject(cardJson, "back", cJSON_CreateString(card -> back));
    saveUserData(user_context);
    *user_context = *initializeUserDataBus();
}

void removeFlashcardFromDeck(cJSON* user_context, int deck_position, int flashcard_position){
    cJSON* decks = cJSON_GetObjectItemCaseSensitive(user_context, "decks");
    cJSON* deck = cJSON_GetArrayItem(decks, deck_position);
    cJSON* jsonDeck = cJSON_GetObjectItemCaseSensitive(deck, "deck");
    cJSON* cards = cJSON_GetObjectItemCaseSensitive(jsonDeck, "cards");
    cJSON* card = cJSON_GetArrayItem(cards, flashcard_position);
    cJSON_DeleteItemFromArray(cards, flashcard_position);
    saveUserData(user_context);
    *user_context = *initializeUserDataBus();
}

void viewFlashcardsFromDeck(cJSON* user_context, int deck_position){
    cJSON* decks = cJSON_GetObjectItemCaseSensitive(user_context, "decks");
    cJSON* deck = cJSON_GetArrayItem(decks, deck_position);
    cJSON* jsonDeck = cJSON_GetObjectItemCaseSensitive(deck, "deck");
    cJSON* cards = cJSON_GetObjectItemCaseSensitive(jsonDeck, "cards");
    cJSON* card = NULL;
    int index = 0;
    cJSON_ArrayForEach(card, cards){
        cJSON* front = cJSON_GetObjectItemCaseSensitive(card, "front");
        cJSON* back = cJSON_GetObjectItemCaseSensitive(card, "back");
        printf("Flashcard %d:\n", index);
        printf("Front: %s\n", front -> valuestring);
        printf("Back: %s\n", back -> valuestring);
        index++;
    }
}

void updateFlashcardFromDeck(cJSON* user_context, int deck_position, int flashcard_position, const char* newFront, const char* newBack){
    cJSON* decks = cJSON_GetObjectItemCaseSensitive(user_context, "decks");
    cJSON* deck = cJSON_GetArrayItem(decks, deck_position);
    cJSON* jsonDeck = cJSON_GetObjectItemCaseSensitive(deck, "deck");
    cJSON* cards = cJSON_GetObjectItemCaseSensitive(jsonDeck, "cards");
    cJSON* card = cJSON_GetArrayItem(cards, flashcard_position);
    cJSON* front = cJSON_GetObjectItemCaseSensitive(card, "front");
    cJSON* back = cJSON_GetObjectItemCaseSensitive(card, "back");
    front -> valuestring = strdup(newFront);
    back -> valuestring = strdup(newBack);
    saveUserData(user_context);
    *user_context = *initializeUserDataBus();
}

void studyDeck(Deck* deck){
    Flashcard* auxCard = deck -> first;
    if (deck -> first != NULL){
        while (auxCard != NULL){
            printf("%s\n", auxCard -> front);
            printf("Pressione enter para ver a resposta...\n");
            getchar();
            printf("%s\n", auxCard -> back);
            printf("Pressione enter para continuar...\n");
            getchar();
            auxCard = auxCard -> next;
        }
    } else {
        printf("Sua lista de flashcards está vazia...\n");
    }
}

#include <decks.h>
#include <user_data_bus.h>

Deck* createDeck(char* deckName, cJSON* user_context){
    Deck* newDeck = (Deck*) malloc(sizeof(Deck));
    cJSON* decks = cJSON_GetObjectItemCaseSensitive(user_context, "decks");
    cJSON* deck = cJSON_CreateObject();
    cJSON_AddItemToArray(decks, deck);
    if (newDeck != NULL){
        newDeck -> label = deckName;
        newDeck -> first = NULL;
        newDeck -> last = NULL;
        newDeck -> next = NULL;
        cJSON* jsonDeck = deckToJson(newDeck);
        cJSON_AddItemToObject(deck, "deck", jsonDeck);
        saveUserData(user_context);
        *user_context = *initializeUserDataBus();
    } else {
        printf("Falha na criação de um novo deck...\n");
    }
    return newDeck;
}

void deleteDeck(int position, cJSON* user_context){
    cJSON* decks = cJSON_GetObjectItemCaseSensitive(user_context, "decks");
    cJSON* deck = cJSON_GetArrayItem(decks, position);
    cJSON_DeleteItemFromArray(decks, position);
    saveUserData(user_context);
    *user_context = *initializeUserDataBus();
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
    cJSON* jsonDeck = cJSON_GetObjectItemCaseSensitive(deck, "deck");
    cJSON* label = cJSON_GetObjectItemCaseSensitive(jsonDeck, "label");
    label -> valuestring = strdup(newLabel);
    saveUserData(user_context);
    *user_context = *initializeUserDataBus();
}


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

void addFlashcardToDeck(Deck* deck, Flashcard* card){
    if (deck -> first == NULL){
        deck -> first = card;
        deck -> last = card;
    } else {
        deck -> last -> next = card;
        deck -> last = card;
    }
}

void removeFlashcardFromDeck(Deck* deck, Flashcard* card){
    Flashcard* auxCard = deck -> first;
    if (deck -> first != NULL){
        if (deck -> first == card){
            deck -> first = card -> next;
            free(card);
        } else {
            while (auxCard -> next != card){
                auxCard = auxCard -> next;
            }
            auxCard -> next = card -> next;
            free(card);
        }
    } else {
        printf("Sua lista de flashcards está vazia...\n");
    }
}

void viewFlashcardsFromDeck(Deck* deck){
    Flashcard* auxCard = deck -> first;
    if (deck -> first != NULL){
        while (auxCard != NULL){
            printf("%s\n", auxCard -> front);
            printf("%s\n", auxCard -> back);
            auxCard = auxCard -> next;
        }
    } else {
        printf("Sua lista de flashcards está vazia...\n");
    }
}

void updateFlashcardFromDeck(Deck* deck, Flashcard* card, const char* front, const char* back){
    Flashcard* auxCard = deck -> first;
    if (deck -> first != NULL){
        if (deck -> first == card){
            card -> front = strdup(back);
            card -> back = strdup(front);
        } else {
            while (auxCard -> next != card){
                auxCard = auxCard -> next;
            }
            card -> front = strdup(back);
            card -> back = strdup(front);
        }
    } else {
        printf("Sua lista de flashcards está vazia...\n");
    }
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

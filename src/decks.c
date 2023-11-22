#include <decks.h>
Deck* createDeck(char* dakeName){
    Deck* newDeck = (Deck*) malloc(sizeof(Deck));
    if (newDeck != NULL){
        newDeck -> label = dakeName;
    } else {
        printf("Falha na criação de um novo deck...\n");
    }
    return newDeck;
    //TUDO: update new deck in file
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
    //TUDO: change the initialization to an initialization that starts with the file.
}

void viewDecks(Decks* decks){
    Deck* auxDeck = decks -> first;
    if (decks -> first != NULL){
        while (auxDeck != NULL){
            printf("%s\n", auxDeck -> label);
            auxDeck = auxDeck -> next;
        }
    } else {
        printf("Sua lista de deks está vazia...\n ");
    }
}

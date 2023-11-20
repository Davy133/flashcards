#include "flashcard.h"

//TODO: Add file I/O for flashcards

Flashcard* createFlashcard(const char* back, const char* front) {
    Flashcard* card = (Flashcard*)malloc(sizeof(Flashcard));
    card->question = strdup(back);
    card->answer = strdup(front);
    return card;
}

void deleteFlashcard(Flashcard* card) {
    free(card->question);
    free(card->answer);
    free(card); 
    //TODO: Delete card from file.
}

void updateFlashcard(Flashcard* card, const char* back, const char* front) {
    free(card->question);
    free(card->answer);
    card->question = strdup(back);
    card->answer = strdup(front);
    //TODO: Update card in file.
}

const char* getFlashcardQuestion(const Flashcard* card) {
    return card->question;
}

const char* getFlashcardAnswer(const Flashcard* card) {
    return card->answer;
}

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
#include <decks.h>

Deck* createDeck(char* deckName){
    Deck* newDeck = (Deck*) malloc(sizeof(Deck));
    if (newDeck != NULL){
        newDeck -> label = deckName;
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
        printf("Sua lista de decks está vazia...\n ");
    }
}

void addFlashcardToDeck(Deck* deck, Flashcard* card){
    if (deck -> first == NULL){
        deck -> first = card;
        deck -> last = card;
    } else {
        deck -> last -> next = card;
        deck -> last = card;
    }
    //TUDO: update deck in file
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
    //TUDO: update deck in file
}

void viewFlashcardsFromDeck(Deck* deck){
    Flashcard* auxCard = deck -> first;
    if (deck -> first != NULL){
        while (auxCard != NULL){
            printf("%s\n", auxCard -> question);
            printf("%s\n", auxCard -> answer);
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
            card -> question = strdup(back);
            card -> answer = strdup(front);
        } else {
            while (auxCard -> next != card){
                auxCard = auxCard -> next;
            }
            card -> question = strdup(back);
            card -> answer = strdup(front);
        }
    } else {
        printf("Sua lista de flashcards está vazia...\n");
    }
    //TUDO: update deck in file
}

void viewFlashcardsFromDeck(Deck* deck){
    Flashcard* auxCard = deck -> first;
    if (deck -> first != NULL){
        while (auxCard != NULL){
            printf("%s\n", auxCard -> question);
            printf("%s\n", auxCard -> answer);
            auxCard = auxCard -> next;
        }
    } else {
        printf("Sua lista de flashcards está vazia...\n");
    }
}

void studyDeck(Deck* deck){
    Flashcard* auxCard = deck -> first;
    if (deck -> first != NULL){
        while (auxCard != NULL){
            printf("%s\n", auxCard -> question);
            printf("Pressione enter para ver a resposta...\n");
            getchar();
            printf("%s\n", auxCard -> answer);
            printf("Pressione enter para continuar...\n");
            getchar();
            auxCard = auxCard -> next;
        }
    } else {
        printf("Sua lista de flashcards está vazia...\n");
    }
}

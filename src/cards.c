#include "cards.h"

//TODO: Add file I/O for flashcards

Flashcard* createFlashcard(const char* back, const char* front) {
    Flashcard* card = (Flashcard*)malloc(sizeof(Flashcard));
    card->front = strdup(back);
    card->back = strdup(front);
    return card;
}

void deleteFlashcard(Flashcard* card) {
    free(card->front);
    free(card->back);
    free(card); 
}

void updateFlashcard(Flashcard* card, const char* back, const char* front) {
    free(card->front);
    free(card->back);
    card->front = strdup(back);
    card->back = strdup(front);
}

const char* getFlashcardfront(const Flashcard* card) {
    return card->front;
}

const char* getFlashcardback(const Flashcard* card) {
    return card->back;
}

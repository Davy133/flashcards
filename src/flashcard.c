#include "include/flashcard.h"

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

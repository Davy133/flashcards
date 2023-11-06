#pragma once
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* question;
    char* answer;
} Flashcard;

Flashcard* createFlashcard(const char* front, const char* back);
void deleteFlashcard(Flashcard* card);
void updateFlashcard(Flashcard* card, const char* front, const char* back);
const char* getFlashcardFront(const Flashcard* card);

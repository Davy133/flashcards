#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Flashcard {
    char* front;
    char* back;
    struct Flashcard* next;
} Flashcard;


Flashcard* createFlashcard(const char* front, const char* back);
void deleteFlashcard(Flashcard* card);
void updateFlashcard(Flashcard* card, const char* front, const char* back);
const char* getFlashcardFront(const Flashcard* card);

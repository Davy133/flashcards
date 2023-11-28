/*
Copyright (c) 2023 Davy Coelho and Contributors

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once
#include "common.h"

typedef struct SuperMemo2 {
    int interval;
    int repetitions;
    float easeFactor;
}SuperMemo2;

typedef struct Flashcard {
    char* UUID;
    char* front;
    char* back;
    unsigned long long dueDate;
    SuperMemo2* sm2;
    struct Flashcard* next;
} Flashcard;

Flashcard* createFlashcard(const char* front, const char* back, char* uuid, SuperMemo2 sm2);
void deleteFlashcard(Flashcard* card);
void updateFlashcard(Flashcard* card, const char* front, const char* back);
const char* getFlashcardFront(const Flashcard* card);

void calculateSuperMemo2(Flashcard* card, int quality);

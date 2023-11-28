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
#include "deck_serializer.h"
#include "cards.h"

typedef struct Deck
{
    char *label;
    Flashcard *first;
    Flashcard *last;
} Deck;

Deck *startDeck();

void createDeck(char *deckName, cJSON *user_context);
void deleteDeck(int position, cJSON *user_context);
void viewDecks(cJSON *user_context);
void viewDeck(cJSON *user_context, int position);
void updateDeck(cJSON *user_context, int position, const char *newLabel);

void addFlashcardToDeck(cJSON *user_context, int deck_position, char *front, char *back);
void removeFlashcardFromDeck(cJSON *user_context, int deck_position, int flashcard_position);
void updateFlashcardFromDeck(cJSON *user_context, int deck_position, int flashcard_position, const char *newFront, const char *newBack);
void viewFlashcardsFromDeck(cJSON *user_context, int deck_position);

void enqueueCard(Deck *deck, Flashcard *card);
Flashcard *dequeueCard(Deck *deck);
int isEmpty(Deck *deck);
void sortDeck(Deck *deck);
void studyDeck(Deck *deck);

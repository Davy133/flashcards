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

#include "cards.h"

Flashcard *createFlashcard(const char *back, const char *front, char *uuid, SuperMemo2 sm2)
{
    Flashcard *card = (Flashcard *)malloc(sizeof(Flashcard));
    card->UUID = strdup(uuid);
    card->front = strdup(back);
    card->back = strdup(front);
    card->sm2 = (SuperMemo2 *)malloc(sizeof(SuperMemo2));
    memcpy(card->sm2, &sm2, sizeof(SuperMemo2));
    return card;
}

void deleteFlashcard(Flashcard *card)
{
    free(card->front);
    free(card->back);
    free(card->sm2);
    free(card);
}

void updateFlashcard(Flashcard *card, const char *back, const char *front)
{
    free(card->front);
    free(card->back);
    card->front = strdup(back);
    card->back = strdup(front);
}

void calculateSuperMemo2(Flashcard *card, int quality)
{
    SuperMemo2 *sm2_Aux = card->sm2;
    if (quality < 0 || quality > 5)
    {
        return;
    }
    if (quality >= 3)
    {
        if (sm2_Aux->repetitions == 0)
        {
            sm2_Aux->interval = 1;
        }
        else if (sm2_Aux->repetitions == 1)
        {
            sm2_Aux->interval = 6;
        }
        else
        {
            sm2_Aux->interval = (int)((sm2_Aux->interval) * (sm2_Aux->easeFactor));
        }
        sm2_Aux->repetitions++;
    }
    else
    {
        sm2_Aux->repetitions = 0;
        sm2_Aux->interval = 1;
    }
    sm2_Aux->easeFactor = (sm2_Aux->easeFactor) + (0.1 - (5 - quality) * (0.08 + (5 - quality) * 0.02));
    if (sm2_Aux->easeFactor < 1.3)
    {
        sm2_Aux->easeFactor = 1.3;
    }
}

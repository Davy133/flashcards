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

#include "menu_handler.h"
#include "cards.h"
#include "decks.h"
#include "deck_serializer.h"
#include "user_data_bus.h"

void actionCreateDeck(cJSON *user_context)
{
    char deckName[256];
    printf("Enter the name of the deck: ");
    scanf("%s", deckName);
    createDeck(deckName, user_context);
}

void actionDeleteDeck(cJSON *user_context)
{
    int position;
    printf("Enter the position of the deck: ");
    scanf("%d", &position);
    deleteDeck(position, user_context);
}

void actionViewDecks(cJSON *user_context)
{
    viewDecks(user_context);
}

void actionUpdateDeck(cJSON *user_context)
{
    int position;
    char newLabel[256];
    printf("Enter the position of the deck: ");
    scanf("%d", &position);
    if(position >= cJSON_GetArraySize(cJSON_GetObjectItemCaseSensitive(user_context, "decks"))){
        printf("Invalid deck position.\n");
        return;
    }
    printf("Enter the new name of the deck: ");
    scanf("%s", newLabel);
    updateDeck(user_context, position, newLabel);
}

void actionCreateFlashcard(cJSON *user_context, int deck_position)
{
    char front[256];
    char back[256];
    printf("Enter the front of the flashcard: ");
    scanf("%s", front);
    printf("Enter the back of the flashcard: ");
    scanf("%s", back);
    addFlashcardToDeck(user_context, deck_position, front, back);
}

void actionDeleteFlashcard(cJSON *user_context, int deck_position)
{
    int flashcard_position;
    printf("Enter the position of the flashcard: ");
    scanf("%d", &flashcard_position);
    if(flashcard_position >= cJSON_GetArraySize(cJSON_GetObjectItemCaseSensitive(user_context, "decks"))){
        printf("Invalid flashcard position.\n");
        return;
    }
    removeFlashcardFromDeck(user_context, deck_position, flashcard_position);
}

void actionViewFlashcards(cJSON *user_context, int deck_position)
{
    if(deck_position >= cJSON_GetArraySize(cJSON_GetObjectItemCaseSensitive(user_context, "decks"))){
        printf("Invalid deck position.\n");
        return;
    }
    viewFlashcardsFromDeck(user_context, deck_position);
}

void actionUpdateFlashcard(cJSON *user_context, int deck_position)
{
    int flashcard_position;
    char newFront[256];
    char newBack[256];
    printf("Enter the position of the flashcard: ");
    scanf("%d", &flashcard_position);
    if(flashcard_position >= cJSON_GetArraySize(cJSON_GetObjectItemCaseSensitive(user_context, "decks"))){
        printf("Invalid flashcard position.\n");
        return;
    }
    printf("Enter the new front of the flashcard: ");
    scanf("%s", newFront);
    printf("Enter the new back of the flashcard: ");
    scanf("%s", newBack);
    updateFlashcardFromDeck(user_context, deck_position, flashcard_position, newFront, newBack);
}

void actionSaveDecksToFile(cJSON *user_context)
{
    char filename[256];
    printf("Enter the name of the file: ");
    scanf("%s", filename);
    printf("Enter the position of the deck: ");
    int deck_position;
    if(deck_position >= cJSON_GetArraySize(cJSON_GetObjectItemCaseSensitive(user_context, "decks"))){
        printf("Invalid deck position.\n");
        return;
    }
    scanf("%d", &deck_position);
    saveDeckToFile(user_context, filename, deck_position);
}

void actionLoadDecksFromFile(cJSON *user_context)
{
    char filename[256];
    printf("Enter the name of the file: ");
    scanf("%s", filename);
    loadDeckFromFile(filename, user_context);
}

void actionManageDeck(cJSON *user_context)
{
    int deck_position;
    printf("Enter the position of the deck: ");
    scanf("%d", &deck_position);
    if(deck_position >= cJSON_GetArraySize(cJSON_GetObjectItemCaseSensitive(user_context, "decks"))){
        printf("Invalid deck position.\n");
        return;
    }

    struct MenuItem manageDeckMenuItems[] = {
        {1, "Create Flashcard", actionCreateFlashcard},
        {2, "Delete Flashcard", actionDeleteFlashcard},
        {3, "Update Flashcard", actionUpdateFlashcard},
        {4, "Back", NULL},
    };

    struct Menu manageDeckMenu = {
        "Manage Deck",
        manageDeckMenuItems,
        sizeof(manageDeckMenuItems) / sizeof(manageDeckMenuItems[0])};

    int choice;

    do
    {
        actionViewFlashcards(user_context, deck_position);
        displayMenu(&manageDeckMenu);
        choice = handleMenuInput(&manageDeckMenu);

        system("clear || cls");
        if (choice >= 1 && choice <= manageDeckMenu.numItems)
        {
            if (manageDeckMenu.items[choice - 1].action != NULL)
            {
                manageDeckMenu.items[choice - 1].action(user_context, deck_position);
            }
        }
        else
        {
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != manageDeckMenu.numItems);
}

void actionStudy()
{
    cJSON *userdata = NULL;
    userdata = initializeUserDataBus();
    Deck *currentDeck = startDeck();
    int deck_position;
    printf("Enter the position of the deck: ");
    scanf("%d", &deck_position);
    if(deck_position >= cJSON_GetArraySize(cJSON_GetObjectItemCaseSensitive(userdata, "decks"))){
        printf("Invalid deck position.\n");
        return;
    }
    cJSON *decks = cJSON_GetObjectItemCaseSensitive(userdata, "decks");
    cJSON *deck = cJSON_GetArrayItem(decks, deck_position);
    cJSON *jsonDeck = cJSON_GetObjectItemCaseSensitive(deck, "deck");
    cJSON *cards = cJSON_GetObjectItemCaseSensitive(jsonDeck, "cards");
    cJSON *card = NULL;
    cJSON_ArrayForEach(card, cards)
    {
        cJSON *front = cJSON_GetObjectItemCaseSensitive(card, "front");
        cJSON *back = cJSON_GetObjectItemCaseSensitive(card, "back");
        cJSON *dueDate = cJSON_GetObjectItemCaseSensitive(card, "dueDate");
        cJSON *sm2 = cJSON_GetObjectItemCaseSensitive(card, "sm2");
        cJSON *interval = cJSON_GetObjectItemCaseSensitive(sm2, "interval");
        cJSON *repetitions = cJSON_GetObjectItemCaseSensitive(sm2, "repetitions");
        cJSON *easeFactor = cJSON_GetObjectItemCaseSensitive(sm2, "easeFactor");
        cJSON *uuid = cJSON_GetObjectItemCaseSensitive(card, "UUID");
        SuperMemo2 sm2_struct = {
            interval->valueint,
            repetitions->valueint,
            easeFactor->valuedouble,
        };
        if (dueDate->valueint <= time(NULL))
        {
            Flashcard *currentCard = createFlashcard(front->valuestring, back->valuestring, uuid->valuestring, sm2_struct);
            enqueueCard(currentDeck, currentCard);
        }
    }
    if (!isEmpty(currentDeck))
    {
        Flashcard *studyingCard;
        while (!isEmpty(currentDeck))
        {
            int rating;
            studyingCard = dequeueCard(currentDeck);
            printf("Front: %s\n", studyingCard->front);
            printf("Press any key to reveal the back of the card.\n");
            getchar();
            getchar();
            printf("Back: %s\n", studyingCard->back);
            printf("How well did you know this card?\n");
            printf("1 - I didn't know it at all\n");
            printf("2 - I knew it, but I had to think about it\n");
            printf("3 - I knew it, but I had to think about it a little\n");
            printf("4 - I knew it, but it took me a while to remember\n");
            printf("5 - I knew it instantly\n");
            scanf("%d", &rating);
            while (rating < 1 || rating > 5)
            {
                printf("Invalid rating. Please try again.\n");
                scanf("%d", &rating);
            }
            calculateSuperMemo2(studyingCard, rating);
            studyingCard->dueDate = time(NULL) + studyingCard->sm2->interval * 86400;
            if (studyingCard->dueDate < time(NULL))
            {
                enqueueCard(currentDeck, studyingCard);
            }
            else
            {
                system("clear || cls");
                printf("You'll see this card again in %d day(s).\n", studyingCard->sm2->interval);
                userdata = initializeUserDataBus();
                decks = cJSON_GetObjectItemCaseSensitive(userdata, "decks");
                deck = cJSON_GetArrayItem(decks, deck_position);
                jsonDeck = cJSON_GetObjectItemCaseSensitive(deck, "deck");
                cards = cJSON_GetObjectItemCaseSensitive(jsonDeck, "cards");
                card = NULL;
                cJSON_ArrayForEach(card, cards)
                {
                    cJSON *uuid = cJSON_GetObjectItemCaseSensitive(card, "UUID");
                    if (strcmp(uuid->valuestring, studyingCard->UUID) == 0)
                    {
                        cJSON *dueDate = cJSON_GetObjectItemCaseSensitive(card, "dueDate");
                        cJSON *sm2 = cJSON_GetObjectItemCaseSensitive(card, "sm2");
                        cJSON *interval = cJSON_GetObjectItemCaseSensitive(sm2, "interval");
                        cJSON *repetitions = cJSON_GetObjectItemCaseSensitive(sm2, "repetitions");
                        cJSON *easeFactor = cJSON_GetObjectItemCaseSensitive(sm2, "easeFactor");
                        dueDate->valueint = studyingCard->dueDate;
                        interval->valueint = studyingCard->sm2->interval;
                        repetitions->valueint = studyingCard->sm2->repetitions;
                        easeFactor->valuedouble = studyingCard->sm2->easeFactor;
                        if (strcmp(uuid->valuestring, studyingCard->UUID) == 0)
                        {
                            cJSON *dueDate = cJSON_GetObjectItemCaseSensitive(card, "dueDate");
                            cJSON *sm2 = cJSON_GetObjectItemCaseSensitive(card, "sm2");
                            cJSON *interval = cJSON_GetObjectItemCaseSensitive(sm2, "interval");
                            cJSON *repetitions = cJSON_GetObjectItemCaseSensitive(sm2, "repetitions");
                            cJSON *easeFactor = cJSON_GetObjectItemCaseSensitive(sm2, "easeFactor");
                            cJSON_SetNumberValue(dueDate, studyingCard->dueDate);
                            cJSON_SetNumberValue(interval, studyingCard->sm2->interval);
                            cJSON_SetNumberValue(repetitions, studyingCard->sm2->repetitions);
                            easeFactor->valuedouble = studyingCard->sm2->easeFactor;
                            saveUserData(userdata);
                            *userdata = *initializeUserDataBus();
                        }
                    }
                }
                deleteFlashcard(studyingCard);
            }
        }
        printf("Congrats, you've finished this deck for now!\n");
    } else{
        printf("There are no cards to study in this deck.\n");
    }
}

void actionManage()
{
    cJSON *userdata = NULL;
    userdata = initializeUserDataBus();

    struct MenuItem manageMenuItems[] = {
        {1, "Create Deck", actionCreateDeck},
        {2, "Delete Deck", actionDeleteDeck},
        {3, "Update Deck", actionUpdateDeck},
        {4, "Manage Deck", actionManageDeck},
        {5, "Save Decks to File", actionSaveDecksToFile},
        {6, "Load Decks from File", actionLoadDecksFromFile},
        {7, "Back", NULL},
    };

    struct Menu manageMenu = {
        "Manage Decks",
        manageMenuItems,
        sizeof(manageMenuItems) / sizeof(manageMenuItems[0])};

    int choice;

    do
    {
        actionViewDecks(userdata);
        displayMenu(&manageMenu);
        choice = handleMenuInput(&manageMenu);

        system("clear || cls");
        if (choice >= 1 && choice <= manageMenu.numItems)
        {
            if (manageMenu.items[choice - 1].action != NULL)
            {
                manageMenu.items[choice - 1].action(userdata);
            }
        }
        else
        {
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != manageMenu.numItems);
    system("clear || cls");
}

int main(void)
{
    system("clear || cls");
    cJSON *userdata = NULL;
    userdata = initializeUserDataBus();
    struct MenuItem mainMenuItems[] = {
        {1, "Study Deck", actionStudy},
        {2, "Manage Decks", actionManage},
        {3, "Quit", NULL},
    };

    struct Menu mainMenu = {
        "Flashcard App Main Menu",
        mainMenuItems,
        sizeof(mainMenuItems) / sizeof(mainMenuItems[0])};

    int choice;

    do
    {
        displayMenu(&mainMenu);
        choice = handleMenuInput(&mainMenu);

        system("clear || cls");
        if (choice >= 1 && choice <= mainMenu.numItems)
        {
            if (mainMenu.items[choice - 1].action != NULL)
            {
                mainMenu.items[choice - 1].action(userdata);
            }
            else
            {
                printf("Goodbye!\n");
            }
        }
        else
        {
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != mainMenu.numItems);

    return 0;
}

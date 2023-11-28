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

void actionCreateDeck(cJSON* user_context, int length){
    char deckName[256];
    printf("Enter the name of the deck: ");
    scanf("%s", deckName);
    createDeck(deckName, user_context);
    loadingDisplay("Creating deck", length);
}

void actionViewDecks(cJSON* user_context, int length){
    viewDecks(user_context, length);
}

void actionDeleteDeck(cJSON* user_context, int length){
    int position;
    actionViewDecks(user_context, length);
    line(length);
    printf("\nEnter the position of the deck: ");
    scanf("%d", &position);
    deleteDeck(position, user_context);
    loadingDisplay("Deleting deck", length);
}

void actionUpdateDeck(cJSON* user_context, int length){
    int position;
    char newLabel[256];
    actionViewDecks(user_context, length);
    line(length);
    printf("\nEnter the position of the deck: ");
    scanf("%d", &position);
    printf("Enter the new name of the deck: ");
    scanf("%s", newLabel);
    updateDeck(user_context, position, newLabel);
    loadingDisplay("Updating deck", length);
}

void actionCreateFlashcard(cJSON* user_context, int deck_position, int length){
    char front[256];
    char back[256];
    printf("Enter the front of the flashcard: ");
    scanf("%s", front);
    printf("Enter the back of the flashcard: ");
    scanf("%s", back);
    addFlashcardToDeck(user_context, deck_position, front, back);
    loadingDisplay("Creating flashcard", length);
}

void actionViewFlashcards(cJSON* user_context, int deck_position, int length){
    viewFlashcardsFromDeck(user_context, deck_position, length);
}

void actionDeleteFlashcard(cJSON* user_context, int deck_position, int length){
    int flashcard_position;
    actionViewFlashcards(user_context, deck_position, length);
    line(length);
    printf("\nEnter the position of the flashcard: ");
    scanf("%d", &flashcard_position);
    removeFlashcardFromDeck(user_context, deck_position, flashcard_position);
    loadingDisplay("Deleting flashcard", length);
}

void actionUpdateFlashcard(cJSON* user_context, int deck_position, int length){
    int flashcard_position;
    char newFront[256];
    char newBack[256];
    actionViewFlashcards(user_context, deck_position, length);
    line(length);
    printf("\nEnter the position of the flashcard: ");
    scanf("%d", &flashcard_position);
    printf("Enter the new front of the flashcard: ");
    scanf("%s", newFront);
    printf("Enter the new back of the flashcard: ");
    scanf("%s", newBack);
    updateFlashcardFromDeck(user_context, deck_position, flashcard_position, newFront, newBack);
    loadingDisplay("Updating flashCard", length);
}

void actionSaveDecksToFile(cJSON* user_context){
    char filename[256];
    printf("Enter the name of the file: ");
    scanf("%s", filename);
    printf("Enter the position of the deck: ");
    int deck_position;
    scanf("%d", &deck_position);
    saveDeckToFile(user_context, filename, deck_position);
}

void actionLoadDecksFromFile(cJSON* user_context){
    char filename[256];
    printf("Enter the name of the file: ");
    scanf("%s", filename);
    loadDeckFromFile(filename, user_context);
}

void actionManageDeck(cJSON* user_context, int length){
    int deck_position;
    actionViewDecks(user_context, length);
    line(length);
    printf("\nEnter the position of the deck: ");
    scanf("%d", &deck_position);
    system("clear || cls");

    struct MenuItem manageDeckMenuItems[] = {
        {1, "Create Flashcard", actionCreateFlashcard},
        {2, "Delete Flashcard", actionDeleteFlashcard},
        {3, "Update Flashcard", actionUpdateFlashcard},
        {4, "Back", NULL},
    };

    struct Menu manageDeckMenu = {
        "M A N A G E  D E C K", 
        manageDeckMenuItems,
        sizeof(manageDeckMenuItems) / sizeof(manageDeckMenuItems[0])
    };

    int choice;

    do {
        actionViewFlashcards(user_context, deck_position, length);
        displayMenu(&manageDeckMenu, length);
        choice = handleMenuInput(&manageDeckMenu);

        system("clear || cls");
        if (choice >= 1 && choice <= manageDeckMenu.numItems) {
            if (manageDeckMenu.items[choice - 1].action != NULL) {
                manageDeckMenu.items[choice - 1].action(user_context, deck_position, length);
            }
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != manageDeckMenu.numItems);
}

void actionManage(cJSON* uc, int length){
    // está iniciando o userdada novamente? Já não tinha sido iniciado no main?
    cJSON* userdata = NULL;
    userdata = initializeUserDataBus();
    Decks* currentDecks = startDecks();
    
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
        "M A N A G E  D E C K S", 
        manageMenuItems,
        sizeof(manageMenuItems) / sizeof(manageMenuItems[0])
    };

    int choice;

    do {
        actionViewDecks(userdata, length);
        displayMenu(&manageMenu, length);
        choice = handleMenuInput(&manageMenu);

        system("clear || cls");
        if (choice >= 1 && choice <= manageMenu.numItems) {
            if (manageMenu.items[choice - 1].action != NULL) {
                manageMenu.items[choice - 1].action(userdata, length);
            }
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != manageMenu.numItems);
    system("clear || cls");
}

int main(void)
{
    system("clear || cls");
    cJSON* userdata = NULL;
    userdata = initializeUserDataBus();
    struct MenuItem mainMenuItems[] = {
        {1, "Manage Decks", actionManage},
        {2, "Quit", NULL},
    };

    struct Menu mainMenu = {
        "F L A S H C A R D  A P P  M A I N  M E N U", 
        mainMenuItems,
        sizeof(mainMenuItems) / sizeof(mainMenuItems[0])
    };

    int choice;
    int length = 80;

    do {
        displayMenu(&mainMenu, length);
        choice = handleMenuInput(&mainMenu);
        
        system("clear || cls");
        if (choice >= 1 && choice <= mainMenu.numItems) {
            if (mainMenu.items[choice - 1].action != NULL) {
                mainMenu.items[choice - 1].action(userdata, length);
            } else {
                printf("Goodbye!");
                mySleep();
                printf(" See you later...\n");
                mySleep(); mySleep();
            }
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != mainMenu.numItems);

    return 0;
}

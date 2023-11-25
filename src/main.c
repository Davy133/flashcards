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
#include "cJSON.h"
#include "deck_serializer.h"
#include "user_data_bus.h"

void actionCreateDeck(cJSON* user_context){
    char deckName[256];
    printf("Enter the name of the deck: ");
    scanf("%s", deckName);
    createDeck(deckName, user_context);
}

void actionDeleteDeck(cJSON* user_context){
    int position;
    printf("Enter the position of the deck: ");
    scanf("%d", &position);
    deleteDeck(position, user_context);
}

void actionViewDecks(cJSON* user_context){
    viewDecks(user_context);
}

void actionUpdateDeck(cJSON* user_context){
    int position;
    char newLabel[256];
    printf("Enter the position of the deck: ");
    scanf("%d", &position);
    printf("Enter the new name of the deck: ");
    scanf("%s", newLabel);
    updateDeck(user_context, position, newLabel);
}

void actionCreateFlashcard(cJSON* user_context){
    char front[256];
    char back[256];
    int deck_position;
    printf("Enter the front of the flashcard: ");
    scanf("%s", front);
    printf("Enter the back of the flashcard: ");
    scanf("%s", back);
    printf("Enter the position of the deck: ");
    scanf("%d", &deck_position);
    Flashcard* card = createFlashcard(front, back);
    addFlashcardToDeck(user_context, deck_position, card);
}

void actionDeleteFlashcard(cJSON* user_context){
    int deck_position;
    int flashcard_position;
    printf("Enter the position of the deck: ");
    scanf("%d", &deck_position);
    printf("Enter the position of the flashcard: ");
    scanf("%d", &flashcard_position);
    removeFlashcardFromDeck(user_context, deck_position, flashcard_position); 
}

void actionViewFlashcards(cJSON* user_context){
    int deck_position;
    printf("Enter the position of the deck: ");
    scanf("%d", &deck_position);
    viewFlashcardsFromDeck(user_context, deck_position);
}

void actionUpdateFlashcard(cJSON* user_context){
    int deck_position;
    int flashcard_position;
    char newFront[256];
    char newBack[256];
    printf("Enter the position of the deck: ");
    scanf("%d", &deck_position);
    printf("Enter the position of the flashcard: ");
    scanf("%d", &flashcard_position);
    printf("Enter the new front of the flashcard: ");
    scanf("%s", newFront);
    printf("Enter the new back of the flashcard: ");
    scanf("%s", newBack);
    updateFlashcardFromDeck(user_context, deck_position, flashcard_position, newFront, newBack);
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

void actionManage(){
    cJSON* userdata = NULL;
    userdata = initializeUserDataBus();
    Decks* currentDecks = startDecks();
    struct MenuItem manageMenuItems[] = {
        {1, "Create Deck", actionCreateDeck},
        {2, "Delete Deck", actionDeleteDeck},
        {3, "View Decks", actionViewDecks},
        {4, "Update Deck", actionUpdateDeck},
        {5, "Create Flashcard", actionCreateFlashcard},
        {6, "Delete Flashcard", actionDeleteFlashcard},
        {7, "View Flashcards", actionViewFlashcards},
        {8, "Update Flashcard", actionUpdateFlashcard},
        {9, "Save Decks to File", actionSaveDecksToFile},
        {10, "Load Decks from File", actionLoadDecksFromFile},
        {11, "Back", NULL},
    };

    struct Menu manageMenu = {
        "Manage Decks",
        manageMenuItems,
        sizeof(manageMenuItems) / sizeof(manageMenuItems[0])
    };

    int choice;

    do {
        displayMenu(&manageMenu);
        choice = handleMenuInput(&manageMenu);

        if (choice >= 1 && choice <= manageMenu.numItems) {
            if (manageMenu.items[choice - 1].action != NULL) {
                manageMenu.items[choice - 1].action(userdata);
            } else {
                printf("Goodbye!\n");
            }
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != manageMenu.numItems);
}

int main(void)
{
    cJSON* userdata = NULL;
    userdata = initializeUserDataBus();
    struct MenuItem mainMenuItems[] = {
        {1, "Manage Decks", actionManage},
        {2, "Quit", NULL},
    };

    struct Menu mainMenu = {
        "Flashcard App Main Menu",
        mainMenuItems,
        sizeof(mainMenuItems) / sizeof(mainMenuItems[0])
    };

    int choice;

    do {
        displayMenu(&mainMenu);
        choice = handleMenuInput(&mainMenu);

        if (choice >= 1 && choice <= mainMenu.numItems) {
            if (mainMenu.items[choice - 1].action != NULL) {
                mainMenu.items[choice - 1].action(userdata);
            } else {
                printf("Goodbye!\n");
            }
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != mainMenu.numItems);

    return 0;
}

#include <stdio.h>
#include "menu.h"
#include "flashcard.h"

void actionStudy() {
    printf("Starting study...\n");
}

void actionCreateFlashcards() {
    char back[256];
    char front[256];
    
    //TODO: Add file I/O for flashcards
    printf("Creating flashcards...\n");

    printf("Enter the back of the card: ");
    scanf("%s", back);

    printf("Enter the front of the card: ");
    scanf("%s", front);

    Flashcard* card = createFlashcard(back, front);
}

void actionViewDecks() {
    printf("Viewing decks...\n");
}

int main() {
    Decks* decks = startDecks();

    struct MenuItem mainMenuItems[] = {
        {1, "Study", actionStudy},
        {2, "Create Flashcards", actionCreateFlashcards},
        {3, "View Decks", actionViewDecks},
        {4, "Quit", NULL},
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
                mainMenu.items[choice - 1].action();
            } else {
                printf("Goodbye!\n");
            }
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != mainMenu.numItems);

    return 0;
}

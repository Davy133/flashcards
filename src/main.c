#include <stdio.h>
#include "include/menu.h"

void actionStudy() {
    printf("Starting study...\n");
}

void actionCreateFlashcards() {
    printf("Creating flashcards...\n");
}

void actionViewDecks() {
    printf("Viewing decks...\n");
}

int main() {
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

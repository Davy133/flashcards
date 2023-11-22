#include <stdio.h>
#include "menu_handler.h"
#include "cards.h"
#include "decks.h"
#include <cjson/cJSON.h>
#include <deck_serializer.h>
#include "user_data_bus.h"

int main(void)
{
    cJSON* userdata = NULL;
    userdata = initializeUserDataBus();
    Deck* deck = createDeck("Teste2", userdata);
    // viewDecks(userdata);
    // deleteDeck(11, userdata);
    // viewDecks(userdata);
    return 0;
}

//     Decks* decks = startDecks();

//     struct MenuItem mainMenuItems[] = {
//         {1, "Study", actionStudy},
//         {2, "Manage Decks", actionManage},
//         {3, "View Decks", actionViewDecks},
//         {4, "Quit", NULL},
//     };

//     struct Menu mainMenu = {
//         "Flashcard App Main Menu",
//         mainMenuItems,
//         sizeof(mainMenuItems) / sizeof(mainMenuItems[0])
//     };

//     int choice;

//     do {
//         displayMenu(&mainMenu);
//         choice = handleMenuInput(&mainMenu);

//         if (choice >= 1 && choice <= mainMenu.numItems) {
//             if (mainMenu.items[choice - 1].action != NULL) {
//                 mainMenu.items[choice - 1].action();
//             } else {
//                 printf("Goodbye!\n");
//             }
//         } else {
//             printf("Invalid choice. Please try again.\n");
//         }
//     } while (choice != mainMenu.numItems);

//     return 0;
// }


// void actionManage() {
//     char back[256];
//     char front[256];

//     //TODO: Add file I/O for flashcards
//     printf("Creating flashcards...\n");

//     printf("Enter the back of the card: ");
//     scanf("%s", back);

//     printf("Enter the front of the card: ");
//     scanf("%s", front);

//     Flashcard* card = createFlashcard(back, front);
// }

// void actionViewDecks() {
//     struct MenuItem mainMenuItems[] = {
//         {1, "Study", actionStudy},
//         {2, "Manage Decks", actionManage},
//         {3, "View Decks", actionViewDecks},
//         {4, "Quit", NULL},
//     };

//     struct Menu mainMenu = {
//         "Flashcard App Main MenuAA",
//         mainMenuItems,
//         sizeof(mainMenuItems) / sizeof(mainMenuItems[0])
//     };

//     int choice;

//     do {
//         displayMenu(&mainMenu);
//         choice = handleMenuInput(&mainMenu);

//         if (choice >= 1 && choice <= mainMenu.numItems) {
//             if (mainMenu.items[choice - 1].action != NULL) {
//                 mainMenu.items[choice - 1].action();
//             } else {
//                 printf("Goodbye!\n");
//             }
//         } else {
//             printf("Invalid choice. Please try again.\n");
//         }
//     } while (choice != mainMenu.numItems);

// }

// void actionSaveDecksToFile(){

// }

// int main() {
//     Decks* decks = startDecks();

//     struct MenuItem mainMenuItems[] = {
//         {1, "Study", actionStudy},
//         {2, "Manage Decks", actionManage},
//         {3, "View Decks", actionViewDecks},
//         {4, "Quit", NULL},
//     };

//     struct Menu mainMenu = {
//         "Flashcard App Main Menu",
//         mainMenuItems,
//         sizeof(mainMenuItems) / sizeof(mainMenuItems[0])
//     };

//     int choice;

//     do {
//         displayMenu(&mainMenu);
//         choice = handleMenuInput(&mainMenu);

//         if (choice >= 1 && choice <= mainMenu.numItems) {
//             if (mainMenu.items[choice - 1].action != NULL) {
//                 mainMenu.items[choice - 1].action();
//             } else {
//                 printf("Goodbye!\n");
//             }
//         } else {
//             printf("Invalid choice. Please try again.\n");
//         }
//     } while (choice != mainMenu.numItems);

//     return 0;
// }

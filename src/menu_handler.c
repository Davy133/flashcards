#include <stdio.h>
#include "menu_handler.h"

void displayMenu(const struct Menu* menu) {
    printf("========================================\n");
    printf("%s\n", menu->title);
    for (int i = 0; i < menu->numItems; i++) {
        printf("%d. %s\n", menu->items[i].id, menu->items[i].label);
    }
    printf("========================================\n");
}

int handleMenuInput(const struct Menu* menu) {
    int choice;
    printf("\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    printf("\n");
    return choice;
}

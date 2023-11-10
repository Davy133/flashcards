#include <stdio.h>
#include "menu.h"

void displayMenu(const struct Menu* menu) {
    printf("%s\n", menu->title);
    for (int i = 0; i < menu->numItems; i++) {
        printf("%d. %s\n", menu->items[i].id, menu->items[i].label);
    }
}

int handleMenuInput(const struct Menu* menu) {
    int choice;
    printf("Enter your choice: ");
    scanf("%d", &choice);
    return choice;
}

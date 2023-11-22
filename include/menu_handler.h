#pragma once 

struct MenuItem {
    int id;
    const char* label;
    void (*action)();
};

struct Menu {
    const char* title;
    struct MenuItem* items;
    int numItems;
};

void displayMenu(const struct Menu* menu);

int handleMenuInput(const struct Menu* menu);

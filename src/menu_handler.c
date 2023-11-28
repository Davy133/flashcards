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

void line (int length){
    for (int i = 0; i < length; i++){
        printf("%c", 205);
    }
    printf("\n");
}

void topMargin(int length){
    printf("%c", 201);
    for (int i = 0; i < length - 2; i++){
        printf("%c", 205);
    }
    printf("%c\n", 187);
    printf("%c%*c\n", 186, length - 1, 186);
}

void downMargin(int length){
    printf("%c%*c\n", 186, length - 1, 186);
    printf("%c", 200);
    for (int i = 0; i < length - 2; i++){
        printf("%c", 205);
    }
    printf("%c\n", 188);
}

int leftIndentCalculation (const struct Menu* menu, int length){
    int largestMenuItem = 0;
    for (int i = 0; i < menu->numItems; i++) {
        if (strlen(menu->items[i].label) > largestMenuItem){
            largestMenuItem = strlen(menu->items[i].label);
        }
    }
    return round((length - largestMenuItem)/2);
}

void displayMenu(const struct Menu* menu, int length) {
    int leftIndent = leftIndentCalculation(menu, length);
    topMargin(length);
    printf("%*s\n\n", (strlen(menu->title)) + (length - strlen(menu->title))/2, menu->title);
    for (int i = 0; i < menu->numItems; i++) {
        printf("%*d. %s\n", leftIndent - 1, menu->items[i].id, menu->items[i].label);
    }
    downMargin(length);
}

int handleMenuInput(const struct Menu* menu) {
    int choice;
    printf("\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    printf("\n");
    return choice;
}

void mySleep(){
    #ifdef _WIN32 || _WIN64
        Sleep(1000); // Sleep 1 segundo
        //Sleep(500); // Sleep 0,5 segundo
    #else
        sleep(1); // Sleep 1 segundo
        //usleep(500*1000);  // Sleep 0,5 segundo (500 milisegundos)
    #endif
}

void loadingDisplay(const char* loading_message, int length){
    system("clear || cls");
    line(length);
    printf("%*s", strlen(loading_message) + (length - strlen(loading_message))/2, loading_message);
    for (int i = 0; i < 3; i++){
        mySleep();
        printf(" .");
    }
    mySleep();
    system("clear || cls");
}
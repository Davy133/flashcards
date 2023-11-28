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

#include "user_data_bus.h"

cJSON *initializeUserDataBus()
{
    if (access("userdata.json", F_OK) != -1)
    {
        FILE *file = fopen("userdata.json", "r");
        if (file != NULL)
        {
            fseek(file, 0, SEEK_END);
            long file_size = ftell(file);
            fseek(file, 0, SEEK_SET);
            char *json_data = malloc(file_size + 1);
            fread(json_data, 1, file_size, file);
            fclose(file);
            cJSON *root = cJSON_Parse(json_data);
            free(json_data);
            // printf("[DATABUS] userdata.json loaded.\n");
            return root;
        }
        else
        {
            printf("Failed to load userdata.json.\n");
        }
    }
    else
    {
        cJSON *root = cJSON_CreateObject();
        cJSON *decks = cJSON_CreateArray();
        cJSON_AddItemToObject(root, "decks", decks);
        char *json_data = cJSON_Print(root);
        FILE *file = fopen("userdata.json", "w");
        if (file != NULL)
        {
            fputs(json_data, file);
            fclose(file);
            // printf("[DATABUS] userdata.json created.\n");
            return root;
        }
        else
        {
            printf("Failed to create userdata.json.\n");
        }
        cJSON_Delete(root);
        free(json_data);
    }
}

void saveUserData(cJSON *root)
{
    char *json_data = cJSON_Print(root);
    FILE *file = fopen("userdata.json", "w");
    if (file != NULL)
    {
        fputs(json_data, file);
        fclose(file);
        // printf("[DATABUS] userdata.json saved.\n");
    }
    else
    {
        printf("Failed to save userdata.json.\n");
    }
    free(json_data);
}

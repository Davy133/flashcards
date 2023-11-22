#pragma once
#include <cards.h> 
#include <decks.h>  
#include <cjson/cJSON.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

cJSON* initializeUserDataBus();
void saveUserData();

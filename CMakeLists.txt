cmake_minimum_required(VERSION 3.22.1)
project(flashcards C)

set(SOURCES
    src/main.c
    src/deck_serializer.c
    src/menu_handler.c
    src/cards.c
    src/decks.c
    src/cJSON.c
    src/user_data_bus.c
)
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC include)

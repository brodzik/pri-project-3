/*
 *  [PRI] Project 3
 *  Playlist manager.
 *
 *  main.c - user and data interaction
 *
 *  Adrian Brodzik
 *  Warsaw University of Technology
 *  Faculty of Electronics and Information Technology
 */

#include "song.h"
#include "genre.h"

#include <stdbool.h>

#ifdef _WIN32
#define CONSOLE_CLEAR_CMD "cls"
#elif __linux__
#define CONSOLE_CLEAR_CMD "clear"
#else
#define CONSOLE_CLEAR_CMD ""
#endif

enum Status { IDLE, PLAYING };
typedef enum Status Status;

void generateTestData(Node **genres)
{
    Node *pop_songs = NULL;
    pushBackSong(&pop_songs, "Bohemian Rhapsody", "Queen");
    pushBackGenre(genres, "Pop", pop_songs);

    Node *rock_songs = NULL;
    pushBackSong(&rock_songs, "Strawberry Fields Forever", "The Beatles");
    pushBackSong(&rock_songs, "Stairway To Heaven", "Led Zeppelin");
    pushBackSong(&rock_songs, "Free Bird", "Lynyrd Skynyrd");
    pushBackGenre(genres, "Rock", rock_songs);

    Node *jazz_songs = NULL;
    pushBackGenre(genres, "Jazz", jazz_songs);

    Node *classical_songs = NULL;
    pushBackGenre(genres, "Classical", classical_songs);
}

void clearScreen()
{
    system(CONSOLE_CLEAR_CMD);
}

void flushInputBuffer()
{
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void handleNextCommand(Status *status, Node *playlist, Node *curent_song)
{
    if (status == NULL)
    {
        printf("Error: NULL pointer to status\n");
        exit(-1);
    }
    else
    {
        if (*status == IDLE)
        {
            printf("Commands:\n");
            printf("1) Play\n");
            printf("2) List\n");
            printf("3) Add\n");
            printf("4) Edit\n");
            printf("5) Remove\n");
            printf("6) Save\n");
            printf("7) Exit\n");
            printf("\n");

            int cmd = 0;

            if (scanf("%d", &cmd) != 1)
            {
                flushInputBuffer();
            }

            clearScreen();

            switch (cmd)
            {
                case 1: // Play
                    break;
                case 2: // List
                    printList(&playlist, genrePrinter);
                    break;
                case 3: // Add
                    break;
                case 4: // Edit
                    break;
                case 5: // Remove
                    break;
                case 6: // Save
                    break;
                case 7: // Exit
                    exit(0);
                    break;
                default: // Invalid
                    printf("Invalid command, try again.\n\n");
                    break;
            }
        }
        else
        {
            printf("Error: unknown status '%d'", *status);
            exit(-1);
        }
    }
}

int main()
{
    // Environment variables
    Status status = IDLE;
    Node *playlist = NULL;
    Node *current_song = NULL;

    // Load demo data
    generateTestData(&playlist);

    // Main event loop
    while (true)
    {
        // Interact with the user and data
        handleNextCommand(&status, playlist, current_song);
    }

    return 0;
}


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

void generateTestData(Node **genres)
{
    Node *pop_songs = NULL;
    pushBackSong(&pop_songs, "Song 1", "Author");
    pushBackSong(&pop_songs, "Song 2", "Author");
    pushBackSong(&pop_songs, "Song 3", "Author");
    pushBackSong(&pop_songs, "Song 4", "Author");
    pushBackSong(&pop_songs, "Song 5", "Author");
    pushBackGenre(genres, "Pop", pop_songs);

    Node *rock_songs = NULL;
    pushBackSong(&rock_songs, "Song 6", "Author");
    pushBackSong(&rock_songs, "Song 7", "Author");
    pushBackSong(&rock_songs, "Song 8", "Author");
    pushBackGenre(genres, "Rock", rock_songs);

    Node *jazz_songs = NULL;
    pushBackGenre(genres, "Jazz", jazz_songs);

    Node *blues_songs = NULL;
    pushBackGenre(genres, "Blues", blues_songs);

    Node *classical_songs = NULL;
    pushBackSong(&classical_songs, "Song 9", "Author");
    pushBackSong(&classical_songs, "Song 10", "Author");
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

int inputInteger()
{
    int i = 0;

    scanf("%d", &i);
    flushInputBuffer();
    clearScreen();

    return i;
}

void handlePlay(Node **playlist)
{
    if (*playlist != NULL)
    {
        Node *current_genre = *playlist;

        if (current_genre->data != NULL)
        {
            Node *first_song = ((Genre*)current_genre->data)->songs;
            Node *last_song = ((Genre*)current_genre->data)->songs->prev;
            Node *current_song = first_song;

            while (true)
            {
                printf("Now playing: %s - %s\n", ((Song*)current_song->data)->artist, ((Song*)current_song->data)->name);
                printf("\n");
                printf("Commands:\n");
                printf("1) Next song\n");
                printf("2) Previous song\n");
                printf("3) Stop\n");
                printf("\n");

                switch (inputInteger())
                {
                    case 1: // Next
                        if (current_song->next == first_song)
                        {
                            // Find next non-empty genre
                            do
                            {
                                current_genre = current_genre->next;
                            }
                            while (((Genre*)current_genre->data)->songs == NULL);

                            first_song = ((Genre*)current_genre->data)->songs;
                            last_song = ((Genre*)current_genre->data)->songs->prev;
                            current_song = first_song;
                        }
                        else
                        {
                            current_song = current_song->next;
                        }

                        break;
                    case 2: // Previous
                        if (current_song->prev == last_song)
                        {
                            // Find previous non-empty genre
                            do
                            {
                                current_genre = current_genre->prev;
                            }
                            while (((Genre*)current_genre->data)->songs == NULL);

                            first_song = ((Genre*)current_genre->data)->songs;
                            last_song = ((Genre*)current_genre->data)->songs->prev;
                            current_song = last_song;
                        }
                        else
                        {
                            current_song = current_song->prev;
                        }

                        break;
                    case 3: // Stop
                        return;
                    default: // Invalid
                        printf("Invalid command, try again.\n\n");
                        break;
                }
            }
        }
    }
}

void handleAdd(Node **playlist)
{
}

void handleEdit(Node **playlist)
{
}

void handleRemove(Node **playlist)
{
}

void handleSave(Node **playlist)
{
}

int main()
{
    Node *playlist = NULL;

    generateTestData(&playlist);

    clearScreen();

    while (true)
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

        switch (inputInteger())
        {
            case 1: // Play
                handlePlay(&playlist);
                break;
            case 2: // List
                printList(&playlist, genrePrinter);
                break;
            case 3: // Add
                handleAdd(&playlist);
                break;
            case 4: // Edit
                handleEdit(&playlist);
                break;
            case 5: // Remove
                handleRemove(&playlist);
                break;
            case 6: // Save
                handleSave(&playlist);
                break;
            case 7: // Exit
                exit(0);
                break;
            default: // Invalid
                printf("Invalid command, try again.\n\n");
                break;
        }
    }

    return 0;
}


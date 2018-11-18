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
    pushBackSong(&pop_songs, "Song 2", "Author");
    pushBackSong(&pop_songs, "Song 3", "Author");
    pushBackSong(&pop_songs, "Song 4", "Author");
    pushBackSong(&pop_songs, "Song 5", "Author");
    pushFrontSong(&pop_songs, "Song 1", "Author");
    pushBackGenre(genres, "Pop", pop_songs);

    Node *rock_songs = NULL;
    pushFrontSong(&rock_songs, "Song 6", "Author");
    pushFrontSong(&rock_songs, "Song 7", "Author");
    pushFrontSong(&rock_songs, "Song 8", "Author");
    insertAfterSong(&rock_songs, "Song 6.5", "Author", 2);
    pushFrontGenre(genres, "Rock", rock_songs);

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

void handleAddSong(Node **playlist)
{
}

void inputString(char *s)
{
    scanf("%100s", s);
    flushInputBuffer();
    clearScreen();
}

void handleAddGenre(Node **playlist)
{
    printf("Genre name: ");
    char name[MAX_STRING];
    inputString(name);

    while (true)
    {
        printf("Add genre:\n");
        printf("1) Push back\n");
        printf("2) Push front\n");
        printf("3) Insert after\n");

        switch (inputInteger())
        {
            case 1:
                pushBackGenre(playlist, name, NULL);
                return;
            case 2:
                pushFrontGenre(playlist, name, NULL);
                return;
            case 3:
                printGenres(playlist, NULL);
                printf("Insert after: ");
                int index = inputInteger();

                if (insertAfterGenre(playlist, name, NULL, index))
                {
                    return;
                }
                else
                {
                    printf("Invalid index, try again.\n\n");
                    break;
                }
            default:
                printf("Invalid command, try again.\n\n");
                break;
        }
    }
}

void handleAdd(Node **playlist)
{
    while (true)
    {
        printf("Add:\n");
        printf("1) Song\n");
        printf("2) Genre\n");
        printf("3) Cancel\n");

        switch (inputInteger())
        {
            case 1: // Add song
                handleAddSong(playlist);
                return;
            case 2: // Add genre
                handleAddGenre(playlist);
                return;
            case 3: // Cancel
                return;
            default: // Invalid
                printf("Invalid command, try again.\n\n");
                break;
        }
    }
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
        printf("4) Remove\n");
        printf("5) Save\n");
        printf("6) Exit\n");
        printf("\n");

        switch (inputInteger())
        {
            case 1: // Play
                handlePlay(&playlist);
                break;
            case 2: // List
                printAll(&playlist);
                break;
            case 3: // Add
                handleAdd(&playlist);
                break;
            case 4: // Remove
                handleRemove(&playlist);
                break;
            case 5: // Save
                handleSave(&playlist);
                break;
            case 6: // Exit
                exit(0);
                break;
            default: // Invalid
                printf("Invalid command, try again.\n\n");
                break;
        }
    }

    return 0;
}


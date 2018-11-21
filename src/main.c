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

void generateTestData(Genre **playlist)
{
    Song *pop_songs = NULL;
    pushBackSong(&pop_songs, "Song 2", "Author");
    pushBackSong(&pop_songs, "Song 3", "Author");
    pushBackSong(&pop_songs, "Song 4", "Author");
    pushBackSong(&pop_songs, "Song 5", "Author");
    pushFrontSong(&pop_songs, "Song 1", "Author");
    pushBackGenre(playlist, "Pop", pop_songs);

    Song *rock_songs = NULL;
    pushFrontSong(&rock_songs, "Song 6", "Author");
    pushFrontSong(&rock_songs, "Song 7", "Author");
    pushFrontSong(&rock_songs, "Song 8", "Author");
    insertAfterSong(&rock_songs, "Song 6.5", "Author", 2);
    pushFrontGenre(playlist, "Rock", rock_songs);

    Song *jazz_songs = NULL;
    pushBackGenre(playlist, "Jazz", jazz_songs);

    Song *blues_songs = NULL;
    pushBackGenre(playlist, "Blues", blues_songs);

    Song *classical_songs = NULL;
    pushBackSong(&classical_songs, "Song 9", "Author");
    pushBackSong(&classical_songs, "Song 10", "Author");
    pushBackGenre(playlist, "Classical", classical_songs);
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

void inputString(char *s)
{
    scanf("%100s", s);
    flushInputBuffer();
    clearScreen();
}

void handlePlay(Genre **playlist)
{
    if (*playlist != NULL)
    {
        Genre *current_genre = *playlist;

        if (current_genre->songs != NULL)
        {
            Song *first_song = current_genre->songs;
            Song *last_song = current_genre->songs->prev;
            Song *current_song = first_song;

            while (true)
            {
                printf("Now playing: %s - %s\n", current_song->artist, current_song->name);
                printf("\n");
                printf("Commands:\n");
                printf("1) Next song\n");
                printf("2) Previous song\n");
                printf("3) Stop\n");
                printf("\n");

                switch (inputInteger())
                {
                    case 1:
                        if (current_song->next == first_song)
                        {
                            do
                            {
                                current_genre = current_genre->next;
                            }
                            while (current_genre->songs == NULL);

                            first_song = current_genre->songs;
                            last_song = current_genre->songs->prev;
                            current_song = first_song;
                        }
                        else
                        {
                            current_song = current_song->next;
                        }

                        break;
                    case 2:
                        if (current_song->prev == last_song)
                        {
                            do
                            {
                                current_genre = current_genre->prev;
                            }
                            while (current_genre->songs == NULL);

                            first_song = current_genre->songs;
                            last_song = current_genre->songs->prev;
                            current_song = last_song;
                        }
                        else
                        {
                            current_song = current_song->prev;
                        }

                        break;
                    case 3:
                        return;
                    default:
                        printf("Invalid command, try again.\n\n");
                        break;
                }
            }
        }
    }
    else
    {
        printf("Nothing to play.\n\n");
    }
}

void handleAddSong(Genre **playlist)
{
    printGenres(playlist, NULL);
    printf("Genre: ");
    int genre_index = inputInteger();

    Genre *genre = getGenre(playlist, genre_index);

    if (genre == NULL)
    {
        printf("Invalid index, try again.\n\n");
    }
    else
    {
        printf("Song name: ");
        char name[MAX_STRING];
        inputString(name);

        printf("Song artist: ");
        char artist[MAX_STRING];
        inputString(artist);

        while (true)
        {
            printf("Add song:\n");
            printf("1) Push back\n");
            printf("2) Push front\n");
            printf("3) Insert after\n");

            switch (inputInteger())
            {
                case 1:
                    pushBackSong(&genre->songs, name, artist);
                    return;
                case 2:
                    pushFrontSong(&genre->songs, name, artist);
                    return;
                case 3:
                    printf("%s:\n", genre->name);
                    printSongs(&genre->songs);
                    printf("Insert after: ");
                    int index = inputInteger();

                    if (insertAfterSong(&genre->songs, name, artist, index))
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
}

void handleAddGenre(Genre **playlist)
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

void handleAdd(Genre **playlist)
{
    while (true)
    {
        printf("Add:\n");
        printf("1) Song\n");
        printf("2) Genre\n");
        printf("3) Cancel\n");

        switch (inputInteger())
        {
            case 1:
                handleAddSong(playlist);
                return;
            case 2:
                handleAddGenre(playlist);
                return;
            case 3:
                return;
            default:
                printf("Invalid command, try again.\n\n");
                break;
        }
    }
}

void handleRemoveSong(Genre **playlist)
{
    printGenres(playlist, NULL);
    printf("Genre: ");
    int genre_index = inputInteger();

    Genre *genre = getGenre(playlist, genre_index);

    if (genre == NULL)
    {
        printf("Invalid index, try again.\n\n");
    }
    else
    {
        printf("%s:\n", genre->name);
        printSongs(&genre->songs);
        printf("Remove song: ");
        int song_index = inputInteger();

        if (!removeSong(&genre->songs, song_index))
        {
            printf("Invalid index, try again.\n\n");
        }
    }
}

void handleRemoveGenre(Genre **playlist)
{
    printGenres(playlist, NULL);
    printf("Genre: ");
    int genre_index = inputInteger();

    Genre *genre = getGenre(playlist, genre_index);

    if (genre == NULL)
    {
        printf("Invalid index, try again.\n\n");
    }
    else
    {
        removeAllSongs(&genre->songs);
        removeGenre(playlist, genre_index);
    }
}

void handleRemove(Genre **playlist)
{
    while (true)
    {
        printf("Remove:\n");
        printf("1) Song\n");
        printf("2) Genre\n");
        printf("3) Cancel\n");

        switch (inputInteger())
        {
            case 1:
                handleRemoveSong(playlist);
                return;
            case 2:
                handleRemoveGenre(playlist);
                return;
            case 3:
                return;
            default:
                printf("Invalid command, try again.\n");
                break;
        }
    }
}

void handleSave(Genre **playlist)
{
}

int main()
{
    Genre *playlist = NULL;
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
            case 1:
                handlePlay(&playlist);
                break;
            case 2:
                printAll(&playlist);
                break;
            case 3:
                handleAdd(&playlist);
                break;
            case 4:
                handleRemove(&playlist);
                break;
            case 5:
                handleSave(&playlist);
                break;
            case 6:
                removeAllGenres(&playlist);
                exit(0);
                break;
            default:
                printf("Invalid command, try again.\n\n");
                break;
        }
    }

    return 0;
}


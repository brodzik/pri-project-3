/*
 *  [PRI] Project 3
 *  Playlist manager.
 *
 *  ui.c - user interaction implementations
 *
 *  Adrian Brodzik
 *  Warsaw University of Technology
 *  Faculty of Electronics and Information Technology
 */

#include "ui.h"

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

bool loadPlaylist(Genre **playlist, char *file_name, LoadFlag flag, char *genre_name)
{
    FILE *file;
    file = fopen(file_name, "r");

    if (file == NULL)
    {
        printf("Failed to load file.\n\n");
        return false;
    }
    else
    {
        if (*playlist != NULL)
        {
            removeAllGenres(playlist);
        }

        void *genre_terminator = safeMalloc(sizeof(Song));
        memset(genre_terminator, 1, sizeof(Song));

        Genre *genre_buffer = (Genre*)safeMalloc(sizeof(Genre));
        Song *song_buffer = (Song*)safeMalloc(sizeof(Song));

        while (fread(genre_buffer, sizeof(Genre), 1, file) == 1)
        {
            Song *songs = NULL;

            while (fread(song_buffer, sizeof(Song), 1, file) == 1)
            {
                if (memcmp(song_buffer, genre_terminator, sizeof(Song)) == 0)
                {
                    break;
                }
                else
                {
                    pushBackSong(&songs, song_buffer->name, song_buffer->artist);
                }
            }

            if (flag == ONLY)
            {
                if (strcmp(genre_buffer->name, genre_name) == 0)
                {
                    pushBackGenre(playlist, genre_buffer->name, songs);
                    break;
                }
            }
            else if (flag == NOT)
            {
                if (strcmp(genre_buffer->name, genre_name) != 0)
                {
                    pushBackGenre(playlist, genre_buffer->name, songs);
                }
            }
            else if (flag == FULL)
            {
                if (songs != NULL)
                {
                     pushBackGenre(playlist, genre_buffer->name, songs);
                }
            }
            else
            {
                pushBackGenre(playlist, genre_buffer->name, songs);
            }
        }

        free(genre_terminator);
        free(genre_buffer);
        free(song_buffer);

        fclose(file);
        printf("File loaded.\n\n");

        return true;
    }
}

void handleLoad(Genre **playlist)
{
    printf("File name: ");
    char file_name[MAX_STRING];
    inputString(file_name);

    loadPlaylist(playlist, file_name, NONE, NULL);
}

void handleSave(Genre **playlist)
{
    printf("File name: ");
    char file_name[MAX_STRING];
    inputString(file_name);

    FILE *file;
    file = fopen(file_name, "w");

    if (file == NULL)
    {
        printf("Failed to save file.\n\n");
    }
    else
    {
        void *genre_terminator = safeMalloc(sizeof(Song));
        memset(genre_terminator, 1, sizeof(Song));

        if (*playlist != NULL)
        {
            Genre *curr_genre = *playlist;

            do
            {
                fwrite(curr_genre, sizeof(Genre), 1, file);

                if (curr_genre->songs != NULL)
                {
                    Song *curr_song = curr_genre->songs;

                    do
                    {
                        fwrite(curr_song, sizeof(Song), 1, file);
                        curr_song = curr_song->next;
                    }
                    while (curr_song != curr_genre->songs);
                }

                fwrite(genre_terminator, sizeof(Song), 1, file);
                curr_genre = curr_genre->next;
            }
            while (curr_genre != *playlist);
        }

        free(genre_terminator);

        fclose(file);
        printf("File saved.\n\n");
    }
}

void generateTestData(Genre **playlist)
{
    Song *pop_songs = NULL;
    pushBackSong(&pop_songs, "Song 1", "Artist 1");
    pushBackSong(&pop_songs, "Song 2", "Artist 2");
    pushBackSong(&pop_songs, "Song 3", "Artist 3");
    pushBackSong(&pop_songs, "Song 4", "Artist 4");
    pushBackSong(&pop_songs, "Song 5", "Artist 5");
    pushBackGenre(playlist, "Pop", pop_songs);

    Song *rock_songs = NULL;
    pushBackSong(&rock_songs, "Song 6", "Artist 6");
    pushBackSong(&rock_songs, "Song 7", "Artist 7");
    pushBackSong(&rock_songs, "Song 8", "Artist 8");
    pushBackGenre(playlist, "Rock", rock_songs);

    Song *jazz_songs = NULL;
    pushBackGenre(playlist, "Jazz", jazz_songs);

    Song *blues_songs = NULL;
    pushBackGenre(playlist, "Blues", blues_songs);

    Song *classical_songs = NULL;
    pushBackSong(&classical_songs, "Song 9", "Artist 9");
    pushBackGenre(playlist, "Classical", classical_songs);
}

void parseArgs(Genre **playlist, int argc, char **argv)
{
    if (argc == 2)
    {
        if (strcmp(argv[1], "start") == 0)
        {
            return;
        }
        else if (strcmp(argv[1], "demo") == 0)
        {
            generateTestData(playlist);
            return;
        }
    }
    else if (argc == 3)
    {
        if (strcmp(argv[1], "load") == 0)
        {
            if (loadPlaylist(playlist, argv[2], NONE, NULL))
            {
                return;
            }
            else
            {
                exit(-1);
            }
        }
    }
    else if (argc == 4)
    {
        if (strcmp(argv[1], "load") == 0 && strcmp(argv[3], "full") == 0)
        {
            if (loadPlaylist(playlist, argv[2], FULL, NULL))
            {
                return;
            }
            else
            {
                exit(-1);
            }
        }
    }
    else if (argc == 5)
    {
        if (strcmp(argv[1], "load") == 0)
        {
            if (strcmp(argv[3], "only") == 0)
            {
                if (loadPlaylist(playlist, argv[2], ONLY, argv[4]))
                {
                    return;
                }
                else
                {
                    exit(-1);
                }
            }
            else if (strcmp(argv[3], "not") == 0)
            {
                if (loadPlaylist(playlist, argv[2], NOT, argv[4]))
                {
                    return;
                }
                else
                {
                    exit(-1);
                }
            }
        }
    }

    printf("Usage:\n");
    printf("    app start                       initializes the app with an empty playlist\n");
    printf("    app demo                        loads a demo playlist\n");
    printf("    app load [file]                 loads an existing playlist\n");
    printf("    app load [file] only [genre]    loads one specific genre from an existing playlist\n");
    printf("    app load [file] not  [genre]    loads all but one specific genre from an existing playlist\n");
    printf("    app load [file] full            loads all non-empty genres from an existing playlist\n");
    exit(-1);
}

void initMainLoop(Genre **playlist)
{
    while (true)
    {
        printf("Commands:\n");
        printf("1) Play\n");
        printf("2) List\n");
        printf("3) Add\n");
        printf("4) Remove\n");
        printf("5) Load\n");
        printf("6) Save\n");
        printf("7) Exit\n");
        printf("\n");

        switch (inputInteger())
        {
            case 1:
                handlePlay(playlist);
                break;
            case 2:
                printAll(playlist);
                break;
            case 3:
                handleAdd(playlist);
                break;
            case 4:
                handleRemove(playlist);
                break;
            case 5:
                handleLoad(playlist);
                break;
            case 6:
                handleSave(playlist);
                break;
            case 7:
                removeAllGenres(playlist);
                exit(0);
                break;
            default:
                printf("Invalid command, try again.\n\n");
                break;
        }
    }
}


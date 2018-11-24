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

void handleLoad(Genre **playlist)
{
    FILE *file;
    file = fopen("data.bin", "r");

    if (file == NULL)
    {
        printf("Failed to load file.\n\n");
    }
    else
    {
        if (*playlist != NULL)
        {
            removeAllGenres(playlist);
        }

        void *genre_term = safeMalloc(sizeof(Song));
        memset(genre_term, 1, sizeof(Song));

        Genre *genre_buffer = (Genre*)safeMalloc(sizeof(Genre));
        Song *song_buffer = (Song*)safeMalloc(sizeof(Song));

        while (fread(genre_buffer, sizeof(Genre), 1, file) == 1)
        {
            Song *songs = NULL;

            while (fread(song_buffer, sizeof(Song), 1, file) == 1)
            {
                if (memcmp(song_buffer, genre_term, sizeof(Song)) == 0)
                {
                    break;
                }
                else
                {
                    pushBackSong(&songs, song_buffer->name, song_buffer->artist);
                }
            }

            pushBackGenre(playlist, genre_buffer->name, songs);
        }

        free(genre_buffer);
        free(song_buffer);

        fclose(file);
    }
}

void handleSave(Genre **playlist)
{
    FILE *file;
    file = fopen("data.bin", "w");

    if (file == NULL)
    {
        printf("Failed to save file.\n\n");
    }
    else
    {
        void *genre_term = safeMalloc(sizeof(Song));
        memset(genre_term, 1, sizeof(Song));

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

                fwrite(genre_term, sizeof(Song), 1, file);
                curr_genre = curr_genre->next;
            }
            while (curr_genre != *playlist);
        }

        fclose(file);
    }
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


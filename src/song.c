/*
 *  [PRI] Project 3
 *  Playlist manager.
 *
 *  song.c - song list implementation
 *
 *  Adrian Brodzik
 *  Warsaw University of Technology
 *  Faculty of Electronics and Information Technology
 */

#include "song.h"

Song *createSong(char *name, char *artist)
{
    Song *new_song = (Song*)malloc(sizeof(Song));

    strncpy(new_song->name, name, MAX_STRING);
    strncpy(new_song->artist, artist, MAX_STRING);

    return new_song;
}

void pushBackSong(Node **head, char *name, char *artist)
{
    pushBack(head, createSong(name, artist), sizeof(Song));
}

void pushFrontSong(Node **head, char *name, char *artist)
{
    pushFront(head, createSong(name, artist), sizeof(Song));
}

void insertAfterSong(Node **head, char *name, char *artist, int index)
{
    insertAfter(head, createSong(name, artist), sizeof(Song), index);
}

void songPrinter(void *data)
{
    if (data != NULL)
    {
        printf("%s - %s\n", ((Song*)data)->name, ((Song*)data)->artist);
    }
}


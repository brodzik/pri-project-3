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

struct Song
{
    char name[MAX_STRING], artist[MAX_STRING];
};

void pushBackSong(Node **head, char *name, char *artist)
{
    Song *new_song = (Song*)malloc(sizeof(Song));

    strncpy(new_song->name, name, MAX_STRING);
    strncpy(new_song->artist, artist, MAX_STRING);

    pushBack(head, new_song, sizeof(Song));
}

void songPrinter(void *data)
{
    if (data != NULL)
    {
        printf("%s - %s\n", ((Song*)data)->name, ((Song*)data)->artist);
    }
}


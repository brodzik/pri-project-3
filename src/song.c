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
#include "genre.h"

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

bool insertAfterSong(Node **head, char *name, char *artist, int index)
{
    return insertAfter(head, createSong(name, artist), sizeof(Song), index);
}

void printSongs(Node *songs)
{
    if (songs != NULL)
    {
        Node *last = songs;
        int i = 1;

        do
        {
            printf("    %d) %s - %s\n", i, ((Song*)last->data)->artist, ((Song*)last->data)->name);

            last = last->next;
            ++i;
        }
        while (last != songs);
    }
    else
    {
        printf("    (Empty)\n");
    }
}


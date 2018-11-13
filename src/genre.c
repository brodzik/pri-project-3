/*
 *  [PRI] Project 3
 *  Playlist manager.
 *
 *  genre.c - genre list implementation
 *  
 *  Adrian Brodzik
 *  Warsaw University of Technology
 *  Faculty of Electronics and Information Technology
 */

#include "genre.h"

struct Genre
{
    char name[MAX_STRING];
    Node *songs;
};

void pushBackGenre(Node **head, char *name, Node *songs)
{
    Genre *new_genre = (Genre*)malloc(sizeof(Genre));

    strncpy(new_genre->name, name, MAX_STRING);
    new_genre->songs = songs;

    pushBack(head, new_genre, sizeof(Genre));
}

void genrePrinter(void *data)
{
    if (data != NULL)
    {
        printf("%s:\n", ((Genre*)data)->name);

        if (((Genre*)data)->songs != NULL)
        {
            printList(&((Genre*)data)->songs, songPrinter);
        }
        
        printf("\n");
    }
}


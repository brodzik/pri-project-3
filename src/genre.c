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

Genre *createGenre(char *name, Node *songs)
{
    Genre *new_genre = (Genre*)malloc(sizeof(Genre));

    strncpy(new_genre->name, name, MAX_STRING);
    new_genre->songs = songs;

    return new_genre;
}

void pushBackGenre(Node **head, char *name, Node *songs)
{
    pushBack(head, createGenre(name, songs), sizeof(Genre));
}

void pushFrontGenre(Node **head, char *name, Node *songs)
{
    pushFront(head, createGenre(name, songs), sizeof(Genre));
}

void insertAfterGenre(Node **head, char *name, Node *songs, int index)
{
    insertAfter(head, createGenre(name, songs), sizeof(Genre), index);
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


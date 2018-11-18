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

bool insertAfterGenre(Node **head, char *name, Node *songs, int index)
{
    return insertAfter(head, createGenre(name, songs), sizeof(Genre), index);
}

void printGenres(Node **head, void (*callback)(Node*))
{
    if (*head != NULL)
    {
        Node *last = *head;
        int i = 1;

        printf("Genres:\n");

        do
        {
            printf("%d) %s\n", i, ((Genre*)last->data)->name);

            if (callback != NULL)
            {
                callback(((Genre*)last->data)->songs);
            }

            last = last->next;
            ++i;
        }
        while (last != *head);

        printf("\n");
    }
}

void printAll(Node **head)
{
    printGenres(head, printSongs);
}

Node *getGenre(Node **head, int index)
{
    Node *last = *head;
    int i = 1;

    while (i != index && last->next != *head)
    {
        ++i;
        last = last->next;
    }

    if (i == index)
    {
        return last;
    }
    else
    {
        return NULL;
    }
}


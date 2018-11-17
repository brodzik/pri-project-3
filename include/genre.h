/*
 *  [PRI] Project 3
 *  Playlist manager.
 *
 *  genre.h - genre list definition
 *
 *  Adrian Brodzik
 *  Warsaw University of Technology
 *  Faculty of Electronics and Information Technology
 */

#pragma once

#include "list.h"
#include "song.h"

typedef struct Genre Genre;
struct Genre
{
    char name[MAX_STRING];
    Node *songs;
};

Genre *createGenre(char *name, Node *songs);

void pushBackGenre(Node **head, char *name, Node *songs);

void pushFrontGenre(Node **head, char *name, Node *songs);

void insertAfterGenre(Node **head, char *name, Node *songs, int index);

void genrePrinter(void *data);


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

void pushBackGenre(Node **head, char *name, Node *songs);

void genrePrinter(void *data);

